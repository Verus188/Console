#pragma once

enum Button {
  BTN_UP,
  BTN_DOWN,
  BTN_LEFT,
  BTN_RIGHT,
  BTN_ACTION,
  BTN_ADDITION,
  BTN_COUNT // эта строчка по сути счетчик для циклов
};

void initInput();
bool isButtonPressed(Button btn);