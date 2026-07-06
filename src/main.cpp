#include "config/Config.h"
#include "server/WebServer.h"

#include <csignal>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    const std::string configPath = argc > 1 ? argv[1] : "config/server.conf";
    const auto config = loadServerConfig(configPath);

    std::cout << "Config file: " << configPath << std::endl;
    std::cout << "Thread count: " << config.threadNum << std::endl;
    std::cout << "Web root: " << config.webroot << std::endl;
    std::cout << "Database: " << config.database << std::endl;
    std::cout << "Log file: " << config.logFile << std::endl;

    std::signal(SIGPIPE, SIG_IGN);

    WebServer server(config);
    if (!server.start()) {
        return 1;
    }

    return 0;
}
