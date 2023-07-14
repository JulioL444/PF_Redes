#ifndef SoundData_h
#define SoundData_h

#include <Arduino.h>

class SoundData {
public:
  static unsigned char getSoundValue(int soundIndex, int byteIndex);
};

#endif
