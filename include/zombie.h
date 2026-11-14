#pragma once
#include "entity.h"
#include "types.h"

class Zombie : public Entity {
public:
  Zombie();
  Zombie(int startX, int startY);

  void update(Position nextPosition);
  Position nextPosition(int playerX, int playerY);
};