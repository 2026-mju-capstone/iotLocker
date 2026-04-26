#include "config.h"
#include "communication.h"

void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10);
  
  Serial.println("\n===== Smart Locker Prototype =====");
  
  // 릴레이 초기화
  pinMode(RELAY_PIN, OUTPUT);
  closeLock(); // 초기 상태는 잠김
  Serial.println("[INIT] Relay initialized. Lock is CLOSED.");
  
  // WiFi 연결
  setupWiFi();
  
  Serial.println("[READY] Starting polling loop...");
  Serial.println("============================");
}

void loop() {
  // 1. 와이파이 연결 상태 확인 및 복구
  checkWiFiConnection();
  
  // 2. 서버에서 명령 가져오기
  PollResult result = pollCommand();
  
  // 3. 명령에 따른 하드웨어 제어 및 ACK 전송
  if (result.command == CMD_OPEN) {
    Serial.print("[UNLOCK] Executing command_id=");
    Serial.println(result.commandId);
    openLock();
    sendAck(result.commandId);
  } 
  else if (result.command == CMD_CLOSE) {
    Serial.print("[LOCK] Executing command_id=");
    Serial.println(result.commandId);
    closeLock();
    sendAck(result.commandId);
  }

  // 4. 대기
  delay(POLL_INTERVAL_MS);
}

// ==== 하드웨어 제어 함수 ====
void openLock() {
  Serial.println(">>> RELAY OFF (전류 차단 -> 열림)");
  digitalWrite(RELAY_PIN, UNLOCK_SIGNAL);
}

void closeLock() {
  Serial.println(">>> RELAY ON (전류 인가 -> 잠김)");
  digitalWrite(RELAY_PIN, LOCK_SIGNAL);
}