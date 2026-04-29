#include "hardware.h"
#include "config.h"

static bool currentlyLocked = true;
static unsigned long unlockTime = 0;

void setupHardware()
{
    pinMode(RELAY_PIN, OUTPUT);
    closeLock(); // 초기 상태는 잠김
    pinMode(BUZZER_PIN, OUTPUT);
    Serial.println("[HW] Relay initialized. Lock is CLOSED.");
}

void openLock()
{
    Serial.println(">>> RELAY OFF (전류 차단 → 열림)");
    digitalWrite(RELAY_PIN, UNLOCK_SIGNAL);
    currentlyLocked = false;
    unlockTime = millis();

    playUnlockSound();
}

void closeLock()
{
    Serial.println(">>> RELAY ON (전류 인가 → 잠김)");
    digitalWrite(RELAY_PIN, LOCK_SIGNAL);
    currentlyLocked = true;
}

bool isLocked()
{
    return currentlyLocked;
}

void checkAutoLock()
{
    if (!currentlyLocked && (millis() - unlockTime >= AUTO_LOCK_MS))
    {
        Serial.println("[AUTO-LOCK] Timeout, locking...");
        closeLock();
    }
}

void playUnlockSound() {
    tone(BUZZER_PIN, 1500, 100);  // 1500Hz로 100ms
    delay(120);
    tone(BUZZER_PIN, 2000, 100);  // 2000Hz로 100ms
    delay(120);
    noTone(BUZZER_PIN);
    Serial.println("[BUZZER] Unlock sound");
}

void playLockSound() {
    tone(BUZZER_PIN, 800, 200);   // 800Hz로 200ms
    delay(220);
    noTone(BUZZER_PIN);
    Serial.println("[BUZZER] Lock sound");
}

void playSuccessMelody() {
    int notes[] = {1318, 1568, 1865, 2093};  // E6, G6, A#6, C7
    int durations[] = {150, 150, 150, 300};
    
    for (int i = 0; i < 4; i++) {
        tone(BUZZER_PIN, notes[i], durations[i]);
        delay(durations[i] + 30);
    }
    noTone(BUZZER_PIN);
    Serial.println("[BUZZER] Success melody");
}

void playErrorBeep() {
    for (int i = 0; i < 3; i++) {
        tone(BUZZER_PIN, 400, 100);  // 낮은 음 3번
        delay(150);
    }
    noTone(BUZZER_PIN);
    Serial.println("[BUZZER] Error beep");
}