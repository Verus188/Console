#include <bullet.h>

void Bullet::update() {
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