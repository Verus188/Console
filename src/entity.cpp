#include <entity.h>

void Entity::update() {
  if (!moveTimer.ready())
    return;

  switch (direction) {
  case Direction::UP:
    y -= speed;
    break;
  case Direction::DOWN:
    y += speed;
    break;
  case Direction::LEFT:
    x -= speed;
    break;
  case Direction::RIGHT:
    x += speed;
    break;
  }
}