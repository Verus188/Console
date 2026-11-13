#pragma once

class Timer {
private:
  unsigned long previousMillis;
  unsigned long interval;

public:
  Timer(unsigned long ms);
  bool ready();
  void reset();
};