#ifndef SoundData_h
#define SoundData_h

#include <Arduino.h>

class SoundData {
public:
  static const unsigned char* getSoundValue(int soundIndex, int& size);
};

#endif
