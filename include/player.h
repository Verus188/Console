#pragma once

class Player {
public:
  Player();
  void update();
  void calculatePlayerPosition(int offsetX, int offsetY);

  int speed;
  int playerPositionX;
  int playerPositionY;
  int lastPlayerPositionX;
  int lastPlayerPositionY;
};