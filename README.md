# RGT_test-1

문제 :

스마트 포인터를 활용한 리소스 관리

1. 문제 설명
   
1) 로그 파일들을 관리하는 LogFileManager 클래스를 구현
2) 여러 로그 파일을 동시에 관리하며, 각 파일에 타임스탬프와 함께 로그를 기록할 수 있어야 함

2. 필수 사항

1) LogFileManager 클래스 정의 (public / private 접근 제한자 명시)
2) 적절한 스마트 포인터 사용으로 파일 핸들 관리
3) openLogFile(const std::string& filename) 메서드
4) writeLog(const std::string& filename, const std::string& message) 메서드
5) readLogs(const std::string& filename) → std::vector<std::string> 반환
6) closeLogFile(const std::string& filename) 메서드
7) 복사 / 이동 생성자 및 대입 연산자 적절히 처리
8) 예외 안전성 보장 (파일 열기 실패, 쓰기 실패 등)
