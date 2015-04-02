#include "Client/Keyboard.h"

namespace Client {
  bool Keyboard::isDown(SysKey::Key key) const {
    return keys[static_cast<unsigned>(key)];
  }

  void Keyboard::handleDown(SysKey::Key key) {
    update(key, true);
  }

  void Keyboard::handleUp(SysKey::Key key) {
    update(key, false);
  }

  void Keyboard::update(SysKey::Key key, bool value) {
    keys[static_cast<unsigned>(key)] = value;
  }
}
