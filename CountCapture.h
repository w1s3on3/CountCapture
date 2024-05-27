#ifndef COUNTCAPTURE_H
#define COUNTCAPTURE_H

#include <EEPROM.h>

class CountCapture {
public:
  CountCapture(int maxCount = 3, unsigned long duration = 15000, unsigned long delay = 2000, int eepromAddress = 0);
  void begin();
  bool update();  

private:
  int _maxCount;
  unsigned long _duration;
  unsigned long _delay;
  int _eepromAddress;
  int _count;
  unsigned long _startTime;
};

#endif
