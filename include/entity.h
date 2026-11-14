#pragma once
#include "timer.h"
#include "types.h"

class Entity {
public:
  Entity() : isActive(false), moveTimer(1000) {}
  Entity(int startX, int startY, int stepPixels, int intervalMs,
         Direction bulletDirection)
      : x(startX), y(startY), speed(stepPixels), isActive(true),
        direction(bulletDirection), moveTimer(intervalMs) {}

  int x;
  int y;
  int speed; // сколько пролетает за шаг
  bool isActive;
  Direction direction;

  void update();

private:
  Timer moveTimer;
};