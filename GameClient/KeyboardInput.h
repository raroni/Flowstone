#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include <stdint.h>
#include "KeyboardEvent.h"

class KeyboardInput {
public:
  void write(KeyboardEvent event);
  KeyboardEvent read(uint16_t index) const;
  uint16_t getCount() const;
  void clear();
private:
  static const uint16_t maxEvents = 512;
  KeyboardEvent list[maxEvents];
  uint16_t count;
};

#endif
