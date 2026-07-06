#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

namespace {

std::string trim(const std::string& value) {
    const auto first = value.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }

    const auto last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

std::map<std::string, std::string> loadConfig(const std::string& path) {
    std::map<std::string, std::string> config;
    std::ifstream input(path);
    if (!input.is_open()) {
        return config;
    }

    std::string line;
    while (std::getline(input, line)) {
        const auto comment = line.find('#');
        if (comment != std::string::npos) {
            line = line.substr(0, comment);
        }

        line = trim(line);
        if (line.empty()) {
            continue;
        }

        const auto equal = line.find('=');
        if (equal == std::string::npos) {
            continue;
        }

        const auto key = trim(line.substr(0, equal));
        const auto value = trim(line.substr(equal + 1));
        if (!key.empty()) {
            config[key] = value;
        }
    }

    return config;
}

std::string getConfigValue(
    const std::map<std::string, std::string>& config,
    const std::string& key,
    const std::string& defaultValue
) {
    const auto it = config.find(key);
    if (it == config.end() || it->second.empty()) {
        return defaultValue;
    }
    return it->second;
}

}  // namespace

int main(int argc, char* argv[]) {
    const std::string configPath = argc > 1 ? argv[1] : "config/server.conf";
    const auto config = loadConfig(configPath);

    const auto port = getConfigValue(config, "port", "8080");
    const auto threadNum = getConfigValue(config, "thread_num", "4");
    const auto webroot = getConfigValue(config, "webroot", "./webroot");
    const auto database = getConfigValue(config, "database", "./data/server.db");
    const auto logFile = getConfigValue(config, "log_file", "./logs/server.log");

    std::cout << "HighPerformanceWebServer v0.1.0" << std::endl;
    std::cout << "Config file: " << configPath << std::endl;
    std::cout << "Listen port: " << port << std::endl;
    std::cout << "Thread count: " << threadNum << std::endl;
    std::cout << "Web root: " << webroot << std::endl;
    std::cout << "Database: " << database << std::endl;
    std::cout << "Log file: " << logFile << std::endl;
    std::cout << "Project skeleton is ready." << std::endl;

    return 0;
}

