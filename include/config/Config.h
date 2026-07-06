#pragma once

#include <string>

struct ServerConfig {
    int port = 8080;
    int threadNum = 4;
    std::string webroot = "./webroot";
    std::string database = "./data/server.db";
    std::string logFile = "./logs/server.log";
};

ServerConfig loadServerConfig(const std::string& path);
