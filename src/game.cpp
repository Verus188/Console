#include "game.h"
#include "gameConfig.h"
#include "player.h"
#include <TFT_eSPI.h>
#include <bullet.h>

Player myPlayer;
TFT_eSPI tft = TFT_eSPI();
const int MAX_BULLETS = 20;
Bullet bullets[MAX_BULLETS];
int activeBullets = 0;

void drawWalls() {
  tft.drawLine(0, 0, MAP_SIZE_X, 0, TFT_GREEN);
  tft.drawLine(0, MAP_SIZE_Y, MAP_SIZE_X, MAP_SIZE_Y, TFT_GREEN);
  tft.drawLine(0, MAP_SIZE_Y, 0, 0, TFT_GREEN);
  tft.drawLine(MAP_SIZE_X, 0, MAP_SIZE_X, MAP_SIZE_Y, TFT_GREEN);
}

bool isOutOfBounds(int x, int y) {
  if (x < 0 || x > MAP_SIZE_X || y < 0 || y > MAP_SIZE_Y) {
    return true;
  }
  return false;
}

void updatePlayer() {
  myPlayer.update();
  tft.drawSpot(myPlayer.lastPlayerPositionX, myPlayer.lastPlayerPositionY, 1,
               TFT_BLACK, TFT_BLACK);
  tft.drawSpot(myPlayer.playerPositionX, myPlayer.playerPositionY, 1, TFT_GREEN,
               TFT_GREEN);
}

void updateBullets() {
  if (myPlayer.justShot && activeBullets < MAX_BULLETS) {
    bullets[activeBullets] =
        Bullet(myPlayer.playerPositionX, myPlayer.playerPositionY, 1,
               myPlayer.viewDirection);
    activeBullets++;
  }

  for (int i = 0; i < activeBullets; i++) {
    tft.drawSpot(bullets[i].x, bullets[i].y, 1, TFT_BLACK, TFT_BLACK);
    bullets[i].update();

    if (!isOutOfBounds(bullets[i].x, bullets[i].y)) {
      tft.drawSpot(bullets[i].x, bullets[i].y, 1, TFT_YELLOW, TFT_YELLOW);
    } else {
      bullets[i] = bullets[activeBullets - 1];
      activeBullets--;
    }
  }
}

void initGame() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  drawWalls();
  updatePlayer();
  myPlayer = Player();
}

void updateGame() {
  updatePlayer();
  updateBullets();
}