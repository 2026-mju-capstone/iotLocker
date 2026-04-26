#include "communication.h"
#include "config.h" // 실제 설정값 불러오기
#include <WiFiS3.h>
#include <ArduinoHttpClient.h>

WiFiClient wifi;
HttpClient client = HttpClient(wifi, SERVER_HOST, SERVER_PORT);

String pollPath = "/api/lockers/" + String(LOCKER_ID) + "/pending";
String ackBasePath = "/api/lockers/" + String(LOCKER_ID) + "/ack/";

void setupWiFi() {
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("[FATAL] WiFi module not found!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  Serial.print("[INFO] Firmware version: ");
  Serial.println(fv);

  Serial.println();
  Serial.print("[CONNECT] Connecting to: ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  int retry = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    retry++;
    if (retry > 30) {
      Serial.println();
      Serial.println("[FAIL] Connection timeout (15 seconds)");
      printWiFiStatus(WiFi.status());
      while (true);
    }
  }

  Serial.println("\n===== WiFi CONNECTED! =====");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void checkWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WARN] WiFi disconnected. Reconnecting...");
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    int retry = 0;
    while (WiFi.status() != WL_CONNECTED && retry < 20) {
      delay(500);
      Serial.print(".");
      retry++;
    }
    Serial.println();
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("[INFO] Reconnected!");
    } else {
      Serial.println("[ERROR] Reconnection failed");
    }
  }
}

long extractCommandId(String json) {
  int idx = json.indexOf("\"command_id\":");
  if (idx < 0) return 0;
  int start = idx + 13;
  int end = json.indexOf(",", start);
  if (end < 0) end = json.indexOf("}", start);
  return json.substring(start, end).toInt();
}

PollResult pollCommand() {
  PollResult result = {CMD_NONE, 0};
  
  Serial.println("[POLL] Checking for commands...");
  client.get(pollPath);
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  if (statusCode != 200) {
    Serial.print("[ERROR] HTTP Status: ");
    Serial.println(statusCode);
    result.command = CMD_ERROR;
    return result;
  }

  if (response.indexOf("\"command\":\"NONE\"") < 0) {
    Serial.print("[RESPONSE] ");
    Serial.println(response);
  }

  if (response.indexOf("\"command\":\"OPEN\"") > 0) {
    result.command = CMD_OPEN;
    result.commandId = extractCommandId(response);
  } else if (response.indexOf("\"command\":\"CLOSE\"") > 0) {
    result.command = CMD_CLOSE;
    result.commandId = extractCommandId(response);
  }

  return result;
}

void sendAck(long commandId) {
  String path = "/api/device/ack/" + String(commandId);
  client.post(path);
  int statusCode = client.responseStatusCode();
  Serial.print("[ACK] Status: ");
  Serial.println(statusCode);
}

void printWiFiStatus(int status) {
  switch (status) {
    case WL_IDLE_STATUS:     Serial.println("WL_IDLE_STATUS"); break;
    case WL_NO_SSID_AVAIL:   Serial.println("WL_NO_SSID_AVAIL (SSID not found)"); break;
    case WL_SCAN_COMPLETED:  Serial.println("WL_SCAN_COMPLETED"); break;
    case WL_CONNECTED:       Serial.println("WL_CONNECTED"); break;
    case WL_CONNECT_FAILED:  Serial.println("WL_CONNECT_FAILED (wrong password?)"); break;
    case WL_CONNECTION_LOST: Serial.println("WL_CONNECTION_LOST"); break;
    case WL_DISCONNECTED:    Serial.println("WL_DISCONNECTED"); break;
    default:                 Serial.println("UNKNOWN"); break;
  }
}