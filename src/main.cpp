#include "game.h"
#include "input.h"
#include <Arduino.h>

void setup() {
  Serial.begin(115200);

  initInput();
  initGame();
}

void loop() { updateGame(); }
