#ifndef KEYBOARD_EVENT_H
#define KEYBOARD_EVENT_H

#include "KeyboardKey.h"

enum class KeyboardEventType {
  Down, Up
};

struct KeyboardEvent {
  KeyboardEventType type;
  KeyboardKey key;
};

#endif
