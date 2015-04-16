#include <string.h>
#include "Client/CommandList.h"

namespace Client {
  void CommandList::writeTestCommand(uint8_t x) {
    writeType(CommandType::Test);
    writeUInt8(x);
  }

  TestCommand CommandList::readTestCommand(uint8_t index) const {
    const char *data = buffer+offsets[index]+sizeof(CommandType);
    TestCommand command;
    command.x = *reinterpret_cast<const uint8_t*>(data);
    return command;
  }

  CommandType CommandList::readType(uint8_t index) const {
    return *reinterpret_cast<const CommandType*>(buffer+offsets[index]);
  }

  void CommandList::writeType(CommandType type) {
    offsets[count] = position;
    count++;
    write(&type, sizeof(type));
  }

  void CommandList::writeUInt8(uint8_t x) {
    write(&x, sizeof(x));
  }

  void CommandList::write(void *data, uint16_t length) {
    memcpy(buffer+position, &data, length);
    position += length;
  }

  void CommandList::clear() {
    position = 0;
    count = 0;
  }
}
