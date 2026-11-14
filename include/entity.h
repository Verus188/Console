#pragma once
#include "timer.h"

class Entity {
public:
  Entity() : x(0), y(0), speed(0), isActive(false), moveTimer(1000) {}
  Entity(int startX, int startY, int stepPixels, int intervalMs)
      : x(startX), y(startY), speed(stepPixels), isActive(true),
        moveTimer(intervalMs) {}

  int x;
  int y;
  int speed;
  bool isActive;

  virtual ~Entity() = default;
  virtual void update();

protected:
  Timer moveTimer;
};