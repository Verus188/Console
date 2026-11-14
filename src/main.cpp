#include "game.h"
#include "input.h"
#include <Arduino.h>
#include <random.h>

// Переменные для статистики
unsigned long lastPrintTime = 0;
const unsigned long PRINT_INTERVAL = 5000; // Обновляем раз в 1 секунду
int loopCounter = 0;

void printMemoryInfo(int currentFps) {
  // Проверяем, прошла ли секунда
  if (millis() - lastPrintTime >= PRINT_INTERVAL) {
    lastPrintTime = millis();

    // Очищаем консоль (ANSI-код)
    Serial.print("\033[2J\033[H");

    // Красивый вывод
    Serial.println("=====================================");
    Serial.println("         SYSTEM MONITOR");
    Serial.println("=====================================");

    // Память
    Serial.printf(" Total Heap:  %u bytes\n", ESP.getHeapSize());
    Serial.printf(" Free Heap:   %u bytes\n", ESP.getFreeHeap());
    Serial.printf(" Min Heap:    %u bytes\n", ESP.getMinFreeHeap());

    // Производительность
    Serial.println("-------------------------------------");
    Serial.printf(" FPS:         %d\n", currentFps);

    // Предупреждение, если памяти осталось мало (меньше 20 КБ)
    if (ESP.getFreeHeap() < 20000) {
      Serial.println(" [WARNING]: LOW MEMORY!");
    }

    Serial.println("=====================================");
  }
}

void setup() {
  Serial.begin(115200);

  // Даем порту время на инициализацию, чтобы первые строки не потерялись
  delay(1000);
  Serial.println("Starting Game...");

  Random::init();
  initInput();
  initGame();
}

void loop() {
  // 1. Игровой цикл
  updateGame();

  // 2. Считаем кадры (FPS)
  loopCounter++;

  // 3. Раз в секунду выводим статистику и сбрасываем счетчик
  if (millis() - lastPrintTime >= PRINT_INTERVAL) {
    int currentFps = loopCounter; // Запоминаем сколько натикало
    loopCounter = 0;              // Сбрасываем для следующей секунды
    printMemoryInfo(currentFps);  // Вызываем функцию вывода
  }
}