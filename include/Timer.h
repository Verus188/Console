#pragma once

class Timer {
private:
  unsigned long previousMillis;
  unsigned long interval;

public:
  explicit Timer(unsigned long ms);
  bool ready();
  void reset();
};