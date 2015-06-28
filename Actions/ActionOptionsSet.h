#ifndef ACTIONS_ACTION_OPTIONS_SET_H
#define ACTIONS_ACTION_OPTIONS_SET_H

#include <stdint.h>

namespace Actions {
  class ActionOptionsSet {
  public:
    void update(const void *data, uint8_t length);
    const void* getData() const;
    uint8_t getLength() const;
  private:
    static const uint8_t capacity = 8;
    char data[capacity];
    uint8_t length = 0;
  };
}

#endif
