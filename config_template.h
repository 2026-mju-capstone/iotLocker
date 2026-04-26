// config_template.h (GitHub 업로드용)
#pragma once
#include <Arduino.h>

// ===== 네트워크 환경 (본인의 환경에 맞게 수정하세요) =====
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";
const char* SERVER_HOST = "192.168.X.X";
const int SERVER_PORT = 8080;

//==== 사물함 ID 및 하드웨어 핀 ====
const int LOCKER_ID = 1;
const int RELAY_PIN = 7;
const int POLL_INTERVAL_MS = 2000;

// ==== H182 Fail-Safe type =====
const int LOCK_SIGNAL   = HIGH;
const int UNLOCK_SIGNAL = LOW;