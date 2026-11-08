#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

constexpr uint8_t btnPin1 = 16;
constexpr uint8_t btnPin2 = 17;
constexpr uint8_t btnPin3 = 19;
constexpr uint8_t btnPin4 = 21;

int playerSpeed = 3;

int playerPositionX = 50;
int playerPositionY = 50;
int lastPlayerPositionX = 50;
int lastPlayerPositionY = 50;

int mapSize = 150;

void drawWalls() {
  tft.drawLine(0, 0, mapSize, 0, TFT_GREEN);
  tft.drawLine(0, mapSize, mapSize, mapSize, TFT_GREEN);
  tft.drawLine(0, mapSize, 0, 0, TFT_GREEN);
  tft.drawLine(mapSize, 0, mapSize, mapSize, TFT_GREEN);
}

void calculatePlayerPosition(int x, int y) {
  lastPlayerPositionX = playerPositionX;
  lastPlayerPositionY = playerPositionY;
  playerPositionX += x;
  playerPositionY += y;

  constexpr uint8_t playerOffset = 2;

  if (playerPositionX < playerOffset) {
    playerPositionX = playerOffset;
  }
  if (playerPositionY < playerOffset) {
    playerPositionY = playerOffset;
  }
  if (playerPositionX > mapSize - playerOffset) {
    playerPositionX = mapSize - playerOffset;
  }
  if (playerPositionY > mapSize - playerOffset) {
    playerPositionY = mapSize - playerOffset;
  }
}

void renderMap() {
  tft.drawSpot(lastPlayerPositionX, lastPlayerPositionY, 1, TFT_BLACK,
               TFT_BLACK);
  tft.drawSpot(playerPositionX, playerPositionY, 1, TFT_GREEN, TFT_GREEN);
}

void setup() {
  Serial.begin(115200);

  pinMode(btnPin1, INPUT_PULLUP);
  pinMode(btnPin2, INPUT_PULLUP);
  pinMode(btnPin3, INPUT_PULLUP);
  pinMode(btnPin4, INPUT_PULLUP);

  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  drawWalls();
  renderMap();
}

void loop() {
  if (digitalRead(btnPin1) == LOW) {
    Serial.println("1");
    calculatePlayerPosition(0, -playerSpeed);
    renderMap();
    delay(50);
  }

  if (digitalRead(btnPin2) == LOW) {
    Serial.println("2");
    calculatePlayerPosition(0, playerSpeed);
    renderMap();
    delay(50);
  }

  if (digitalRead(btnPin3) == LOW) {
    Serial.println("3");
    calculatePlayerPosition(-playerSpeed, 0);
    renderMap();
    delay(50);
  }

  if (digitalRead(btnPin4) == LOW) {
    Serial.println("4");
    calculatePlayerPosition(playerSpeed, 0);
    renderMap();
    delay(50);
  }
}
