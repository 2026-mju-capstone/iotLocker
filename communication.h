#pragma once
#include <Arduino.h>

// 서버에서 받은 명령의 종류를 정의 (DB enum과 일치: OPEN, LOCK)
enum LockerCommand {
  CMD_NONE,
  CMD_OPEN,
  CMD_LOCK,
  CMD_ERROR
};

// 명령 결과와 ID를 함께 반환하기 위한 구조체
struct PollResult {
  LockerCommand command;
  long commandId;
};

// 통신 관련 함수 선언
void setupWiFi();
bool checkWiFiConnection();
PollResult pollCommand();
void sendAck(long commandId);
void printWiFiStatus(int status);