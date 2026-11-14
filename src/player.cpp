#include "player.h"
#include "gameConfig.h"
#include <Arduino.h>
#include <input.h>

Player::Player()
    : Entity(50, 50, 1, 20), direction(Direction::RIGHT), shootTimer(200) {
  lastPlayerPositionX = x;
  lastPlayerPositionY = y;
  justShot = false;
}

void Player::calculatePlayerPosition(int offsetX, int offsetY) {
  lastPlayerPositionX = x;
  lastPlayerPositionY = y;
  x += offsetX;
  y += offsetY;

  constexpr uint8_t playerSizeOffset =
      2; // чтоб не вылезал за границы карты с учетом своего размера

  if (x < playerSizeOffset) {
    x = playerSizeOffset;
  }
  if (y < playerSizeOffset) {
    y = playerSizeOffset;
  }
  if (x > MAP_SIZE_X - playerSizeOffset) {
    x = MAP_SIZE_X - playerSizeOffset;
  }
  if (y > MAP_SIZE_Y - playerSizeOffset) {
    y = MAP_SIZE_Y - playerSizeOffset;
  }
}

void Player::update() {
  int moveX = 0;
  int moveY = 0;
  justShot = false;

  if (isButtonPressed(BTN_UP)) {
    direction = Direction::UP;
    moveY -= speed;
  }
  if (isButtonPressed(BTN_DOWN)) {
    direction = Direction::DOWN;
    moveY += speed;
  }
  if (isButtonPressed(BTN_LEFT)) {
    direction = Direction::LEFT;
    moveX -= speed;
  }
  if (isButtonPressed(BTN_RIGHT)) {
    direction = Direction::RIGHT;
    moveX += speed;
  }

  if ((moveX != 0 || moveY != 0) && moveTimer.ready()) {
    calculatePlayerPosition(moveX, moveY);
  }

  if (isButtonPressed(BTN_ACTION) && shootTimer.ready()) {
    justShot = true;
  }
}
