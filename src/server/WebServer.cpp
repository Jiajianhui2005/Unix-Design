#include "server/WebServer.h"

#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <utility>

namespace {

constexpr int kBacklog = 128;
constexpr int kRequestBufferSize = 4096;

std::string fixedHtmlBody() {
    return "<!doctype html>\n"
           "<html lang=\"zh-CN\">\n"
           "<head>\n"
           "    <meta charset=\"utf-8\">\n"
           "    <title>HighPerformanceWebServer</title>\n"
           "</head>\n"
           "<body>\n"
           "    <h1>HighPerformanceWebServer v0.2</h1>\n"
           "    <p>Blocking socket server is running.</p>\n"
           "</body>\n"
           "</html>\n";
}

std::string buildHttpResponse() {
    const auto body = fixedHtmlBody();
    return "HTTP/1.1 200 OK\r\n"
           "Content-Type: text/html; charset=utf-8\r\n"
           "Content-Length: " + std::to_string(body.size()) + "\r\n"
           "Connection: close\r\n"
           "\r\n" +
           body;
}

bool sendAll(int fd, const std::string& data) {
    const char* buffer = data.data();
    std::size_t remaining = data.size();

    while (remaining > 0) {
        const auto sent = ::send(fd, buffer, remaining, 0);
        if (sent < 0) {
            if (errno == EINTR) {
                continue;
            }
            return false;
        }
        if (sent == 0) {
            return false;
        }

        buffer += sent;
        remaining -= static_cast<std::size_t>(sent);
    }

    return true;
}

}  // namespace

WebServer::WebServer(ServerConfig config) : config_(std::move(config)) {}

bool WebServer::start() {
    const int listenFd = createListenSocket();
    if (listenFd < 0) {
        return false;
    }

    std::cout << "HighPerformanceWebServer v0.2.0" << std::endl;
    std::cout << "Listen port: " << config_.port << std::endl;
    std::cout << "Blocking socket server is running." << std::endl;
    std::cout << "Open http://127.0.0.1:" << config_.port << "/ in your browser." << std::endl;

    acceptLoop(listenFd);
    ::close(listenFd);
    return true;
}

int WebServer::createListenSocket() const {
    const int listenFd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (listenFd < 0) {
        std::cerr << "socket failed: " << std::strerror(errno) << std::endl;
        return -1;
    }

    int reuse = 1;
    if (::setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        std::cerr << "setsockopt failed: " << std::strerror(errno) << std::endl;
        ::close(listenFd);
        return -1;
    }

    sockaddr_in address {};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(static_cast<uint16_t>(config_.port));

    if (::bind(listenFd, reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0) {
        std::cerr << "bind failed: " << std::strerror(errno) << std::endl;
        ::close(listenFd);
        return -1;
    }

    if (::listen(listenFd, kBacklog) < 0) {
        std::cerr << "listen failed: " << std::strerror(errno) << std::endl;
        ::close(listenFd);
        return -1;
    }

    return listenFd;
}

void WebServer::acceptLoop(int listenFd) const {
    while (true) {
        sockaddr_in clientAddress {};
        socklen_t clientAddressLength = sizeof(clientAddress);
        const int clientFd = ::accept(
            listenFd,
            reinterpret_cast<sockaddr*>(&clientAddress),
            &clientAddressLength
        );

        if (clientFd < 0) {
            if (errno == EINTR) {
                continue;
            }
            std::cerr << "accept failed: " << std::strerror(errno) << std::endl;
            continue;
        }

        char clientIp[INET_ADDRSTRLEN] {};
        ::inet_ntop(AF_INET, &clientAddress.sin_addr, clientIp, sizeof(clientIp));
        std::cout << "Accepted connection from " << clientIp << ":"
                  << ntohs(clientAddress.sin_port) << std::endl;

        handleClient(clientFd);
        ::close(clientFd);
    }
}

void WebServer::handleClient(int clientFd) const {
    char buffer[kRequestBufferSize] {};
    const auto received = ::recv(clientFd, buffer, sizeof(buffer) - 1, 0);
    if (received < 0) {
        std::cerr << "recv failed: " << std::strerror(errno) << std::endl;
        return;
    }

    if (received == 0) {
        return;
    }

    buffer[received] = '\0';
    std::cout << "Request received:" << std::endl;
    std::cout << buffer << std::endl;

    const auto response = buildHttpResponse();
    if (!sendAll(clientFd, response)) {
        std::cerr << "send failed: " << std::strerror(errno) << std::endl;
    }
}
