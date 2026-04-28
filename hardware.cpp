#include "hardware.h"
#include "config.h"

static bool currentlyLocked = true;
static unsigned long unlockTime = 0;

void setupHardware()
{
    pinMode(RELAY_PIN, OUTPUT);
    closeLock(); // 초기 상태는 잠김
    Serial.println("[HW] Relay initialized. Lock is CLOSED.");
}

void openLock()
{
    Serial.println(">>> RELAY OFF (전류 차단 → 열림)");
    digitalWrite(RELAY_PIN, UNLOCK_SIGNAL);
    currentlyLocked = false;
    unlockTime = millis();
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