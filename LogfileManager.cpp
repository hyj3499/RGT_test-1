#include "LogFileManager.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

// 생성자 및 소멸자
LogFileManager::LogFileManager() = default;
LogFileManager::~LogFileManager() = default;

// 타임스탬프 생성: [YYYY-MM-DD HH:MM:SS] 형식
std::string LogFileManager::getCurrentTimestamp() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "[%Y-%m-%d %H:%M:%S] ");
    return oss.str();
}

void LogFileManager::openLogFile(const std::string& filename) {

    if (logFiles.find(filename) != logFiles.end()) return;

    // std::make_unique를 사용하여 fstream 객체 생성
    // ios::app 모드로 열어 기존 로그 뒤에 추가되도록 설정
    auto file = std::make_unique<std::fstream>(filename, std::ios::in | std::ios::out | std::ios::app);

    if (!file->is_open()) {
        throw std::runtime_error("파일 열기 실패: " + filename);
    }

    // 스마트 포인터의 소유권을 map으로 이동
    logFiles[filename] = std::move(file);
}

void LogFileManager::writeLog(const std::string& filename, const std::string& message) {
    auto it = logFiles.find(filename);
    if (it == logFiles.end()) {
        throw std::runtime_error("파일이 열려있지 않습니다: " + filename);
    }

    // 역참조를 통해 실제 fstream 객체에 접근
    *(it->second) << getCurrentTimestamp() << message << std::endl;

    if (it->second->fail()) {
        throw std::runtime_error("로그 기록 실패: " + filename);
    }
}

std::vector<std::string> LogFileManager::readLogs(const std::string& filename) {
    auto it = logFiles.find(filename);
    if (it == logFiles.end()) {
        throw std::runtime_error("파일이 열려있지 않습니다: " + filename);
    }

    // 읽기 전 포인터를 파일 처음으로 이동
    it->second->clear();
    it->second->seekg(0, std::ios::beg);

    std::vector<std::string> logs;
    std::string line;
    while (std::getline(*(it->second), line)) {
        if (!line.empty()) {
            logs.push_back(line);
        }
    }
    return logs;
}

void LogFileManager::closeLogFile(const std::string& filename) {
    auto it = logFiles.find(filename);
    if (it != logFiles.end()) {
        // 스마트 포인터는 map에서 삭제되는 순간 자동으로 메모리를 해제하고 파일을 닫음
        logFiles.erase(it);
    }
}