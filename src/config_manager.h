#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>  // Updated include path for nlohmann-json

using json = nlohmann::json;


class TestConfigManager {
    private:
        std::string dbHost;
        std::string dbPort;
        std::string dbName;
        std::string dbUser;
        std::string dbPassword;
    public:
        TestConfigManager() {
            dbHost = "localhost";
            dbPort = "5432";
            dbName = "test_db";
            dbUser = "test_user";
            dbPassword = "test_password";
        }

        std::string getDbHost() {
            return dbHost;
        }

        std::string getDbPort() {
            return dbPort;
        }

        std::string getDbName() {
            return dbName;
        }

        std::string getDbUser() {
            return dbUser;
        }

        std::string getDbPassword() {
            return dbPassword;
        }
};


// function to test the ConfigManager class
void testConfigManager() {
    TestConfigManager configManager;
    std::cout << "DB Host: " << configManager.getDbHost() << std::endl;
    std::cout << "DB Port: " << configManager.getDbPort() << std::endl;
    std::cout << "DB Name: " << configManager.getDbName() << std::endl;
    std::cout << "DB User: " << configManager.getDbUser() << std::endl;
    std::cout << "DB Password: " << configManager.getDbPassword() << std::endl;
}

class ConfigManager {
public:
    bool loadConfig(const std::string& environment) {
        std::string configFile = "../../config/" + environment + "_config.json";
        std::ifstream file(configFile, std::ifstream::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open config file: " << configFile << "\n";
            return false;
        }

        json config;
        file >> config;
        file.close();

        // Load environment-specific settings
        dbHost = config["db_host"].get<std::string>();
        dbPort = config["db_port"].get<std::string>();
        dbName = config["db_name"].get<std::string>();
        dbUser = config["db_user"].get<std::string>();
        dbPassword = config["db_password"].get<std::string>();

        return true;
    }

    // Database configuration
    std::string dbHost;
    std::string dbPort;
    std::string dbName;
    std::string dbUser;
    std::string dbPassword;
};

#endif
