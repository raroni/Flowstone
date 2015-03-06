#include "Keyboard.h"

bool Keyboard::isDown(KeyboardKey key) const {
  return keys[static_cast<unsigned>(key)];
}

void Keyboard::handleDown(KeyboardKey key) {
  update(key, true);
}

void Keyboard::handleUp(KeyboardKey key) {
  update(key, false);
}

void Keyboard::update(KeyboardKey key, bool value) {
  keys[static_cast<unsigned>(key)] = value;
}
