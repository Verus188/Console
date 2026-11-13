#include "player.h"
#include "gameConfig.h"
#include <Arduino.h>
#include <input.h>

Player::Player() : moveTimer(50), shootTimer(200) {
  speed = 3;
  playerPositionX = 50;
  playerPositionY = 50;
  lastPlayerPositionX = 50;
  lastPlayerPositionY = 50;
  viewDirection = Direction::RIGHT;
  justShot = false;
}

void Player::calculatePlayerPosition(int offsetX, int offsetY) {
  lastPlayerPositionX = playerPositionX;
  lastPlayerPositionY = playerPositionY;
  playerPositionX += offsetX;
  playerPositionY += offsetY;

  constexpr uint8_t playerSizeOffset =
      2; // чтоб не вылезал за границы карты с учетом своего размера

  if (playerPositionX < playerSizeOffset) {
    playerPositionX = playerSizeOffset;
  }
  if (playerPositionY < playerSizeOffset) {
    playerPositionY = playerSizeOffset;
  }
  if (playerPositionX > MAP_SIZE_X - playerSizeOffset) {
    playerPositionX = MAP_SIZE_X - playerSizeOffset;
  }
  if (playerPositionY > MAP_SIZE_Y - playerSizeOffset) {
    playerPositionY = MAP_SIZE_Y - playerSizeOffset;
  }
}

void Player::update() {
  int moveX = 0;
  int moveY = 0;
  justShot = false;

  if (isButtonPressed(BTN_UP)) {
    viewDirection = Direction::UP;
    moveY -= speed;
  }
  if (isButtonPressed(BTN_DOWN)) {
    viewDirection = Direction::DOWN;
    moveY += speed;
  }
  if (isButtonPressed(BTN_LEFT)) {
    viewDirection = Direction::LEFT;
    moveX -= speed;
  }
  if (isButtonPressed(BTN_RIGHT)) {
    viewDirection = Direction::RIGHT;
    moveX += speed;
  }

  if ((moveX != 0 || moveY != 0) && moveTimer.ready()) {
    calculatePlayerPosition(moveX, moveY);
  }

  if (isButtonPressed(BTN_ACTION) && shootTimer.ready()) {
    justShot = true;
  }
}
