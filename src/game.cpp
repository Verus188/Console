#include "game.h"
#include "player.h"
#include <TFT_eSPI.h>

Player myPlayer;
TFT_eSPI tft = TFT_eSPI();
int mapSize = 238;

void drawWalls() {
  tft.drawLine(0, 0, mapSize, 0, TFT_VIOLET);
  tft.drawLine(0, mapSize, mapSize, mapSize, TFT_VIOLET);
  tft.drawLine(0, mapSize, 0, 0, TFT_VIOLET);
  tft.drawLine(mapSize, 0, mapSize, mapSize, TFT_VIOLET);
}

void renderMap() {
  tft.drawSpot(myPlayer.lastPlayerPositionX, myPlayer.lastPlayerPositionY, 1,
               TFT_BLACK, TFT_BLACK);
  tft.drawSpot(myPlayer.playerPositionX, myPlayer.playerPositionY, 1,
               TFT_VIOLET, TFT_VIOLET);
}

void initGame() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  drawWalls();
  renderMap();
  myPlayer = Player();
}

void updateGame() {
  myPlayer.update();
  renderMap();
}