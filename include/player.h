#pragma once
#include "Timer.h"
#include "types.h"
class Player {
public:
  Player();
  void update();
  void calculatePlayerPosition(int offsetX, int offsetY);

  int speed;
  int playerPositionX;
  int playerPositionY;
  int lastPlayerPositionX;
  int lastPlayerPositionY;
  bool justShot = false;
  Direction viewDirection;

private:
  Timer moveTimer;
  Timer shootTimer;
};