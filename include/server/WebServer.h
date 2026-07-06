#pragma once

#include "config/Config.h"

class WebServer {
public:
    explicit WebServer(ServerConfig config);

    bool start();

private:
    int createListenSocket() const;
    void acceptLoop(int listenFd) const;
    void handleClient(int clientFd) const;

    ServerConfig config_;
};
