#include <assert.h>
#include "KeyboardInput.h"

void KeyboardInput::write(KeyboardEvent event) {
  assert(count != maxEvents);
  if(count == maxEvents) {
    return;
  }
  list[count++] = event;
}

void KeyboardInput::clear() {
  count = 0;
}

KeyboardEvent KeyboardInput::read(uint16_t index) const {
  return list[index];
}

uint16_t KeyboardInput::getCount() const {
  return count;
}
