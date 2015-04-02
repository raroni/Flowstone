#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "SysKey/Key.h"

class Keyboard {
public:
  bool isDown(SysKey::Key key) const;
  void handleDown(SysKey::Key key);
  void handleUp(SysKey::Key key);
private:
  void update(SysKey::Key key, bool value);
  bool keys[static_cast<int>(SysKey::Key::Count)] = { false };
};

#endif
