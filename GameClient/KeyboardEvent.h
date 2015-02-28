#ifndef KEYBOARD_EVENT_H
#define KEYBOARD_EVENT_H

#include "KeyboardEventKey.h"

enum class KeyboardEventType {
  Down, Up
};

struct KeyboardEvent {
  KeyboardEventType type;
  KeyboardEventKey key;
};

#endif
