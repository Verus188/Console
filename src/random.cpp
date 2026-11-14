#include "Random.h"
#include <Arduino.h>
#include <random>

std::mt19937 rng;

void Random::init() {
  rng.seed(esp_random()); // Инициализируем аппаратным шумом ESP32
}

int Random::get(int min, int max) {
  std::uniform_int_distribution<int> dist(min, max);
  return dist(rng);
}