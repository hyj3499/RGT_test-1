#include "LogFileManager.h"
#include <iostream>

int main() {
    try {
        LogFileManager manager;

        manager.openLogFile("error.log");
        manager.openLogFile("debug.log");
        manager.openLogFile("info.log");

        manager.writeLog("error.log", "Database connection failed");
        manager.writeLog("debug.log", "User login attempt");
        manager.writeLog("info.log", "Server started successfully");

        std::vector<std::string> errorLogs = manager.readLogs("error.log");

        for (size_t i = 0; i < errorLogs.size(); ++i) {
            std::cout << "errorLogs[" << i << "] = \"" << errorLogs[i] << "\"" << std::endl;
        }

    } catch (const std::exception& e) {
        // 예외 발생 시 처리
        std::cerr << "런타임 에러: " << e.what() << std::endl;
        return 1;
    } 

    return 0;
}