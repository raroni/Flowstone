#ifndef CLIENT_COMMAND_LIST_H
#define CLIENT_COMMAND_LIST_H

#include <stdint.h>
#include "Client/Commands.h"
#include "Client/CommandType.h"

namespace Client {
  class CommandList {
  public:
    void writeTestCommand(uint8_t x);
    CommandType readType(uint8_t index) const;
    TestCommand readTestCommand(uint8_t index) const;
    void clear();
  private:
    void writeType(CommandType type);
    void writeUInt8(uint8_t n);
    void write(void *data, uint16_t length);
    static const uint8_t max = 20;
    static const uint16_t capacityPerCommand = 1024;
    static const uint16_t capacity = capacityPerCommand*max;
    char buffer[capacity];
    uint16_t offsets[max];
    uint16_t position = 0;
    uint8_t count = 0;
  };
}

#endif
