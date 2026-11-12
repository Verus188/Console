#include "input.h"
#include <Arduino.h>

// Здесь мы ОДИН РАЗ задаем пины. Больше нигде они не упоминаются.
constexpr uint8_t buttonPins[BTN_COUNT] = {
    16, // BTN_UP
    17, // BTN_DOWN
    19, // BTN_LEFT
    21, // BTN_RIGHT
};

void initInput() {
  for (int i = 0; i < BTN_COUNT; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

bool isButtonPressed(Button btn) { return digitalRead(buttonPins[btn]) == LOW; }