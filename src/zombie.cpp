#include "zombie.h"

Zombie::Zombie() : Entity() {};
Zombie::Zombie(int startX, int startY) : Entity(startX, startY, 1, 150) {};

Position Zombie::nextPosition(int playerX, int playerY) {
  Position nextPos = {x, y};

  if (playerX > x) {
    nextPos.x += speed;
  } else if (playerX < x) {
    nextPos.x -= speed;
  }

  if (playerY > y) {
    nextPos.y += speed;
  } else if (playerY < y) {
    nextPos.y -= speed;
  }

  return nextPos;
}

void Zombie::update(Position nextPosition) {
  if (!moveTimer.ready()) {
    return;
  }

  x = nextPosition.x;
  y = nextPosition.y;
}