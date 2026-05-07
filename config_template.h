#pragma once
#include <Arduino.h>

// ===== 네트워크 환경 (본인의 환경에 맞게 수정하세요) =====
constexpr char* WIFI_SSID = "YOUR_WIFI_SSID";
constexpr char* WIFI_PASS = "YOUR_WIFI_PASSWORD";
constexpr char* SERVER_HOST = "192.168.X.X";
constexpr int SERVER_PORT = 8080;

//==== 사물함 ID 및 하드웨어 핀 ====
constexpr int LOCKER_ID = 1;
constexpr int RELAY_PIN = 7;
constexpr int POLL_INTERVAL_MS = 2000;
// ==== H182 Fail-Safe type =====
constexpr int LOCK_SIGNAL   = HIGH;
constexpr int UNLOCK_SIGNAL = LOW;

constexpr int BUZZER_PIN = 8;          // 부저 신호 핀

// 효과음 주파수 설정
constexpr int TONE_UNLOCK_FREQ = 1500; // 열림: 높은 음
constexpr int TONE_LOCK_FREQ = 800;    // 잠김: 낮은 음
constexpr int TONE_DURATION_MS = 200;  // 음 지속 시간