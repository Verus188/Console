#include <bullet.h>

void Bullet::update() {
  if (!moveTimer.ready())
    return;

  switch (direction) {
  case Direction::UP:
    y -= stepPixels;
    break;
  case Direction::DOWN:
    y += stepPixels;
    break;
  case Direction::LEFT:
    x -= stepPixels;
    break;
  case Direction::RIGHT:
    x += stepPixels;
    break;
  }
}