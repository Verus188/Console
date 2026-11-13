#pragma once
#include "Timer.h"
#include "types.h"

class Bullet {
public:
  Bullet() : isActive(false), moveTimer(1000) {}
  Bullet(int startX, int startY, int stepPixels, int intervalMs,
         Direction bulletDirection)
      : x(startX), y(startY), stepPixels(stepPixels), isActive(true),
        direction(bulletDirection), moveTimer(intervalMs) {}

  int x;
  int y;
  int stepPixels; // сколько пролетает за шаг
  bool isActive;
  Direction direction;

  void update();

private:
  Timer moveTimer;
};