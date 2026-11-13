#include "Timer.h"
#include <Arduino.h>

Timer::Timer(unsigned long ms) : interval(ms), previousMillis(0) {}

bool Timer::ready() {
  if (millis() - previousMillis >= interval) {
    previousMillis = millis();
    return true;
  }
  return false;
}

void Timer::reset() { previousMillis = millis(); }