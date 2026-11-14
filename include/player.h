#pragma once
#include "entity.h"
#include "timer.h"
#include "types.h"
class Player : public Entity {
public:
  Player();
  void update() override;
  void calculatePlayerPosition(int offsetX, int offsetY);

  int lastPlayerPositionX;
  int lastPlayerPositionY;
  bool justShot = false;
  Direction direction;

private:
  Timer shootTimer;
};