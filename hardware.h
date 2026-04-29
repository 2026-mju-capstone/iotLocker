#pragma once
#include <Arduino.h>

void setupHardware();
void openLock();
void closeLock();
bool isLocked();

// 자동 잠금 체크 (loop에서 매번 호출)
void checkAutoLock();

void playUnlockSound();
void playLockSound()
void playSuccessMelody();
void playErrorBeep();