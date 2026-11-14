#include "game.h"
#include "gameConfig.h"
#include "player.h"
#include <TFT_eSPI.h>
#include <bullet.h>

Player myPlayer;
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

const int MAX_BULLETS = 20;
Bullet bullets[MAX_BULLETS];
int activeBullets = 0;

void drawWalls() {
  sprite.drawLine(0, 0, MAP_SIZE_X - 2, 0, TFT_GREEN);
  sprite.drawLine(0, MAP_SIZE_Y - 2, MAP_SIZE_X - 2, MAP_SIZE_Y - 2, TFT_GREEN);
  sprite.drawLine(0, MAP_SIZE_Y - 2, 0, 0, TFT_GREEN);
  sprite.drawLine(MAP_SIZE_X - 2, 0, MAP_SIZE_X - 2, MAP_SIZE_Y - 2, TFT_GREEN);
}

bool isOutOfBounds(int x, int y) {
  if (x < 0 || x > MAP_SIZE_X || y < 0 || y > MAP_SIZE_Y) {
    return true;
  }
  return false;
}

void drawPlayer() {
  sprite.drawSpot(myPlayer.playerPositionX, myPlayer.playerPositionY, 1,
                  TFT_GREEN, TFT_GREEN);
}

void updateBullets() {
  // если игрок выстрелил, то добавляем пулю, если еще есть место в массиве пуль
  if (myPlayer.justShot && activeBullets < MAX_BULLETS) {
    bullets[activeBullets] =
        Bullet(myPlayer.playerPositionX, myPlayer.playerPositionY, 3, 20,
               myPlayer.viewDirection);
    activeBullets++;
  }

  // обновляем пули, удаляем те, что за экраном
  for (int i = 0; i < activeBullets; i++) {
    bullets[i].update();

    if (isOutOfBounds(bullets[i].x, bullets[i].y)) {
      bullets[i] = bullets[activeBullets - 1];
      activeBullets--;
    }
  }
}

void drawBullets() {
  for (int i = 0; i < activeBullets; i++) {
    sprite.drawSpot(bullets[i].x, bullets[i].y, 1, TFT_YELLOW, TFT_YELLOW);
  }
}

void initGame() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  if (!sprite.createSprite(MAP_SIZE_X, MAP_SIZE_Y)) {
    Serial.println("Failed to create sprite");
  }

  sprite.fillScreen(TFT_BLACK);
  drawWalls();
  drawPlayer();
  myPlayer = Player();
}

void updateGame() {
  myPlayer.update();
  updateBullets();

  sprite.fillScreen(TFT_BLACK);

  drawWalls();
  drawPlayer();
  drawBullets();

  sprite.pushSprite(MAP_OFFSET_X, MAP_OFFSET_Y);
}