#include "game.h"
#include "gameConfig.h"
#include "player.h"
#include <TFT_eSPI.h>
#include <projectile.h>
#include <random.h>
#include <zombie.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

const int MAX_BULLETS = 20;
Projectile bullets[MAX_BULLETS];
int activeBullets = 0;

Player myPlayer;

Timer enemySpawnTimer(5000);
const int MAX_ENEMIES = 10;
int activeZombies = 0;
Zombie zombies[MAX_ENEMIES];

void drawWalls() {
  sprite.drawLine(0, 0, MAP_SIZE_X - 2, 0, TFT_GREEN);
  sprite.drawLine(0, MAP_SIZE_Y - 2, MAP_SIZE_X - 2, MAP_SIZE_Y - 2, TFT_GREEN);
  sprite.drawLine(0, MAP_SIZE_Y - 2, 0, 0, TFT_GREEN);
  sprite.drawLine(MAP_SIZE_X - 2, 0, MAP_SIZE_X - 2, MAP_SIZE_Y - 2, TFT_GREEN);
}

void spawnEnemy() {
  if (enemySpawnTimer.ready()) {
    int enemyX = Random::get(1, MAP_SIZE_X - 2);
    int enemyY = Random::get(1, MAP_SIZE_Y - 2);

    // Создаем врага и добавляем его в массив врагов
    // activeZombies
    if (activeZombies < MAX_ENEMIES) {
      zombies[activeZombies] = Zombie(enemyX, enemyY);
      activeZombies++;
    }
  }
}

bool isOutOfBounds(int x, int y) {
  if (x < 0 || x > MAP_SIZE_X || y < 0 || y > MAP_SIZE_Y) {
    return true;
  }
  return false;
}

void drawPlayer() {
  sprite.drawSpot(myPlayer.x, myPlayer.y, 1, TFT_GREEN, TFT_GREEN);
}

void updateBullets() {
  // если игрок выстрелил, то добавляем пулю, если еще есть место в массиве пуль
  if (myPlayer.justShot && activeBullets < MAX_BULLETS) {
    bullets[activeBullets] =
        Projectile(myPlayer.x, myPlayer.y, 3, 20, myPlayer.direction);
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

void updateZombies() {
  for (int i = 0; i < activeZombies; i++) {
    Position nextPosition = zombies[i].nextPosition(myPlayer.x, myPlayer.y);
    bool collision = false;

    // коллизия
    for (int j = 0; j < activeZombies; j++) {
      if (i == j)
        continue;

      // Если расстояние между ними меньше размера зомби
      if (abs(nextPosition.x - zombies[j].x) < 2 &&
          abs(nextPosition.y - zombies[j].y) < 2) {
        collision = true;
        break;
      }
    }

    if (!collision) {
      zombies[i].update(nextPosition);
    }
  }
}

void drawZombies() {
  for (int i = 0; i < activeZombies; i++) {
    sprite.drawSpot(zombies[i].x, zombies[i].y, 1, TFT_RED, TFT_RED);
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
  updateZombies();

  spawnEnemy();

  sprite.fillScreen(TFT_BLACK);

  drawWalls();
  drawPlayer();
  drawBullets();
  drawZombies();

  sprite.pushSprite(MAP_OFFSET_X, MAP_OFFSET_Y);
}