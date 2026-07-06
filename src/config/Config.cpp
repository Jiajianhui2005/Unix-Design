#include "config/Config.h"

#include <fstream>
#include <map>
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

std::map<std::string, std::string> loadKeyValueConfig(const std::string& path) {
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

std::string getStringValue(
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

int getIntValue(
    const std::map<std::string, std::string>& config,
    const std::string& key,
    int defaultValue
) {
    const auto value = getStringValue(config, key, "");
    if (value.empty()) {
        return defaultValue;
    }

    try {
        return std::stoi(value);
    } catch (...) {
        return defaultValue;
    }
}

}  // namespace

ServerConfig loadServerConfig(const std::string& path) {
    const auto values = loadKeyValueConfig(path);

    ServerConfig config;
    config.port = getIntValue(values, "port", config.port);
    config.threadNum = getIntValue(values, "thread_num", config.threadNum);
    config.webroot = getStringValue(values, "webroot", config.webroot);
    config.database = getStringValue(values, "database", config.database);
    config.logFile = getStringValue(values, "log_file", config.logFile);

    return config;
}
