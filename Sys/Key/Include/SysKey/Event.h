#ifndef SYSKEY_EVENT_H
#define SYSKEY_EVENT_H

#include "SysKey/Key.h"

namespace SysKey {
  enum class EventType {
    Down, Up
  };

  struct Event {
    EventType type;
    Key key;
  };
}

#endif
