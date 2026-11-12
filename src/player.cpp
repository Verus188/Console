#include "player.h"
#include <Arduino.h>
#include <input.h>

Player::Player() {
  speed = 3;
  playerPositionX = 50;
  playerPositionY = 50;
  lastPlayerPositionX = 50;
  lastPlayerPositionY = 50;
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
  if (playerPositionX > 238 - playerSizeOffset) {
    playerPositionX = 238 - playerSizeOffset;
  }
  if (playerPositionY > 238 - playerSizeOffset) {
    playerPositionY = 238 - playerSizeOffset;
  }
}

void Player::update() {
  int moveX = 0;
  int moveY = 0;

  if (isButtonPressed(BTN_UP))
    moveY -= speed;
  if (isButtonPressed(BTN_DOWN))
    moveY += speed;
  if (isButtonPressed(BTN_LEFT))
    moveX -= speed;
  if (isButtonPressed(BTN_RIGHT))
    moveX += speed;

  if (moveX != 0 || moveY != 0) {
    calculatePlayerPosition(moveX, moveY);
    delay(50);
  }
}
