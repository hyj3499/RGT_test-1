#ifndef LOG_FILE_MANAGER_H
#define LOG_FILE_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <memory>  
#include <fstream> 

// LogFileManager 클래스 정의
class LogFileManager {
private:
    // std::map을 사용하여 error.log, debug.log, info.log 여러 개의 파일을 하나의 manager 객체에서 파일을 동시에 관리
    // fstream* 대신 스마트 포인터 std::unique_ptr를 사용하여 클래스 소멸 시 파일 핸들이 자동으로 닫히도록 설계 (RAII)
    std::map<std::string, std::unique_ptr<std::fstream>> logFiles;

    // 타임스탬프 문자열 생성
    std::string getCurrentTimestamp();

public:
    // 생성자 및 소멸자
    LogFileManager();
    ~LogFileManager();

    // unique_ptr는 복사가 불가능하므로, 클래스 전체의 복사를 금지
    LogFileManager(const LogFileManager&) = delete;
    LogFileManager& operator=(const LogFileManager&) = delete;

    // 이동 생성자 및 이동 대입 연산자, 이동만 허용
    LogFileManager(LogFileManager&& other) noexcept = default;
    LogFileManager& operator=(LogFileManager&& other) noexcept = default;

    // openLogFile 메서드
    void openLogFile(const std::string& filename);
    // writeLog 메서드
    void writeLog(const std::string& filename, const std::string& message);
    // readLogs(const std::string& filename) → std::vector<std::string> 반환
    std::vector<std::string> readLogs(const std::string& filename);
    // closeLogFile 메서드
    void closeLogFile(const std::string& filename);
};

#endif 