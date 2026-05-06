#include "config.h"
#include "hardware.h"
#include "communication.h"

void setup() {
    Serial.begin(9600);
    while (!Serial) delay(10);

    Serial.println("\n===== Smart Locker Prototype =====");

    //하드웨어 초기화 (릴레이 포함)
    setupHardware();

    //WiFi 연결
    setupWiFi();

    Serial.println("[READY] Starting polling loop...");
    Serial.println("============================");
}

void loop() {
    //연결 확인 (실패 시 폴링 건너뜀)
    if (!checkWiFiConnection()) {
        delay(5000);
        return;
    }

    // auto lock 삭제 
    //서버에서 명령 폴링
    PollResult result = pollCommand();

    //명령 처리
    if (result.command == CMD_OPEN) {
        Serial.print("[UNLOCK] Executing command_id=");
        Serial.println(result.commandId);
        openLock();
        sendAck(result.commandId);
    }
    else if (result.command == CMD_LOCK) {
        Serial.print("[LOCK] Executing command_id=");
        Serial.println(result.commandId);
        closeLock();
        sendAck(result.commandId);
    }

    //대기
    delay(POLL_INTERVAL_MS);
}