#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "KeyboardKey.h"

class Keyboard {
public:
  bool isDown(KeyboardKey key) const;
  void handleDown(KeyboardKey key);
  void handleUp(KeyboardKey key);
private:
  void update(KeyboardKey key, bool value);
  bool keys[static_cast<int>(KeyboardKey::Count)] = { false };
};

#endif
