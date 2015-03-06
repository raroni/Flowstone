#include "MacOSX/SysKey.h"

namespace SysKey {
  static const uint8_t maxCount = 128;
  static SysKey::Event events[maxCount];
  static uint8_t count = 0;
  static uint8_t cursor = 0;

  static SysKey::Key convertKeyCode(unsigned short keyCode);

  void handleNSEvent(NSEvent *nsEvent) {
    assert(maxCount != count);
    if(maxCount == count) {
      return;
    }
    SysKey::Event sysEvent;
    sysEvent.key = convertKeyCode(nsEvent.keyCode);
    if(nsEvent.type == NSKeyDown) {
      sysEvent.type = SysKey::EventType::Down;
    } else {
      sysEvent.type = SysKey::EventType::Up;
    }
    events[count++] = sysEvent;
  }

  bool pollEvent(Event &event) {
    if(cursor == count) {
      return false;
    }
    event = events[cursor++];
    return true;
  }

  void clear() {
    count = 0;
    cursor = 0;
  }

  static SysKey::Key convertKeyCode(unsigned short keyCode) {
    if(keyCode > 127) return SysKey::Key::Unknown;

    static const SysKey::Key table[] = {
      SysKey::Key::A,
      SysKey::Key::S,
      SysKey::Key::D,
      SysKey::Key::F,
      SysKey::Key::H,
      SysKey::Key::G,
      SysKey::Key::Z,
      SysKey::Key::X,
      SysKey::Key::C,
      SysKey::Key::V,
      SysKey::Key::Unknown,
      SysKey::Key::B,
      SysKey::Key::Q,
      SysKey::Key::W,
      SysKey::Key::E,
      SysKey::Key::R,
      SysKey::Key::Y,
      SysKey::Key::T,
      SysKey::Key::Num1,
      SysKey::Key::Num2,
      SysKey::Key::Num3,
      SysKey::Key::Num4,
      SysKey::Key::Num6,
      SysKey::Key::Num5,
      SysKey::Key::Unknown,
      SysKey::Key::Num9,
      SysKey::Key::Num7,
      SysKey::Key::Unknown,
      SysKey::Key::Num8,
      SysKey::Key::Num0,
      SysKey::Key::Unknown,
      SysKey::Key::O,
      SysKey::Key::U,
      SysKey::Key::Unknown,
      SysKey::Key::I,
      SysKey::Key::P,
      SysKey::Key::Enter,
      SysKey::Key::L,
      SysKey::Key::J,
      SysKey::Key::Unknown,
      SysKey::Key::K,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Comma,
      SysKey::Key::Unknown,
      SysKey::Key::N,
      SysKey::Key::M,
      SysKey::Key::Period,
      SysKey::Key::Tab,
      SysKey::Key::Space,
      SysKey::Key::Unknown,
      SysKey::Key::Backspace,
      SysKey::Key::Unknown,
      SysKey::Key::Escape,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Capslock,
      SysKey::Key::LeftAlt,
      SysKey::Key::LeftControl,
      SysKey::Key::RightShift,
      SysKey::Key::RightAlt,
      SysKey::Key::RightControl,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Unknown,
      SysKey::Key::Left,
      SysKey::Key::Right,
      SysKey::Key::Down,
      SysKey::Key::Up,
      SysKey::Key::Unknown
    };

    return table[keyCode];
  }
}
