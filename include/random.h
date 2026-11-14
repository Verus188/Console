#pragma once

class Random {
public:
  // Вызывается ОДИН РАЗ в setup()
  static void init();

  // Получить случайное число от min до max (включительно)
  static int get(int min, int max);

private:
  // Статический генератор (один на всю программу)
  static unsigned long seed;
};