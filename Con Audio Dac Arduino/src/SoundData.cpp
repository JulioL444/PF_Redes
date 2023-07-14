#include "SoundData.h"

unsigned char rawData[5][2] = {
  {0x52, 0x49}, // Sonido 1
  {0x41, 0x42}, // Sonido 2
  {0x43, 0x44}, // Sonido 3
  {0x45, 0x46}, // Sonido 4
  {0x47, 0x48}  // Sonido 5
};

unsigned char SoundData::getSoundValue(int soundIndex, int byteIndex) {
  if (soundIndex >= 0 && soundIndex < sizeof(rawData) / sizeof(rawData[0])) {
    if (byteIndex >= 0 && byteIndex < sizeof(rawData[0])) {
      return rawData[soundIndex][byteIndex];
    }
  }
  return 0;
}
