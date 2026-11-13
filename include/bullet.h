#pragma once
#include "types.h"

class Bullet {
public:
  Bullet() : isActive(false) {}
  Bullet(int startX, int startY, int bulletSpeed, Direction bulletDirection)
      : x(startX), y(startY), speed(bulletSpeed), direction(bulletDirection),
        isActive(true) {}

  int x;
  int y;
  int speed;
  bool isActive;
  Direction direction;

  void update();
};