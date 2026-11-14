#pragma once
#include "entity.h"
#include "types.h"

class Projectile : public Entity {
public:
  Projectile() : direction(Direction::RIGHT) {}
  Projectile(int startX, int startY, int stepPixels, int intervalMs,
             Direction projectileDirection)
      : Entity(startX, startY, stepPixels, intervalMs),
        direction(projectileDirection) {}

  Direction direction;

  void update() override;
};
