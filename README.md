# Smart Locker Client (Arduino)

스마트 사물함 제어 시스템의 아두이노 클라이언트 저장소입니다. Arduino Uno R4 WiFi를 통해 Spring Boot 서버와 HTTP 통신을 수행하며, 서버 명령에 따라 솔레노이드 잠금장치를 제어합니다.

## 1. 하드웨어 구성
* **MCU:** Arduino Uno R4 WiFi
* **Actuator:** H182 Fail-Safe 솔레노이드 (전류 인가 시 잠김, 차단 시 열림)
* **Control:** 릴레이 모듈 (제어 핀: D7)
* **Buzzer:** passive buzzer(제어 핀: D8)

## 2. 주요 기능
* **명령 폴링:** 2초(2000ms) 주기로 서버 API(`/api/lockers/{id}/pending`) 확인
* **하드웨어 제어:** 수신된 명령(OPEN/CLOSE)에 따라 릴레이 상태 변경
* **상태 동기화:** 명령 수행 후 서버에 결과 확인(ACK) 응답 전송

## 3. 프로젝트 구조
* `SmartLocker.ino`: 메인 루프 및 하드웨어 제어 로직
* `communication.cpp` / `.h`: WiFi 연결 및 HTTP 통신 모듈
* `config_template.h`: 네트워크 및 서버 환경변수 템플릿

## 4. 설정 및 빌드 방법

### 환경 변수 설정
보안을 위해 와이파이 비밀번호 및 서버 IP가 포함된 파일은 Git으로 추적하지 않습니다. 
코드를 클론한 뒤, `config_template.h` 파일을 복사하여 `config.h` 파일을 생성하고 본인의 환경에 맞게 값을 수정하세요.

```cpp
// config.h
const char* WIFI_SSID = "Your_WiFi_SSID";
const char* WIFI_PASS = "Your_WiFi_Password";
const char* SERVER_HOST = "Your_Server_IP"; // ex: 10.67.214.181
const int SERVER_PORT = 8080;