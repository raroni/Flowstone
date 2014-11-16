#ifndef RENDERING2_COMMAND_STREAM_H
#define RENDERING2_COMMAND_STREAM_H

#include <assert.h>
#include <string.h>
#include "Rendering2/Config.h"
#include "Rendering2/CommandType.h"
#include "Rendering2/Commands.h"

namespace Rendering2 {
  struct OrderKey {
    uint32_t layer : 4;
    // other order params
  };

  struct OrderRecord {
    OrderKey key;
    uint16_t offset;
  };

  class CommandStream {
    char buffer[Config::commandStreamSize];
    uint16_t position = 0;
    OrderRecord orderRecords[512];
    uint16_t count = 0;
  private:
    void write(const void *data, uint16_t length, OrderKey key) {
      assert(position+length <= Config::commandStreamSize);
      memcpy(&buffer[position], data, length);
      orderRecords[count++] = { key, position };
      position += length;
    }
  public:
    void writeDrawAnimatedMesh(DrawAnimatedMeshCommand command, OrderKey key) {
      write(&command, sizeof(command), key);
    }
    void writeChangeShader(ChangeShaderCommand &command, OrderKey key) {
      write(&command, sizeof(command), key);
    }
    void sort() {

    }
    const char* get(uint16_t position) {
      OrderRecord &record = orderRecords[position];
      return &buffer[record.offset];
    }
    void clear() {
      position = 0;
      count = 0;
    }
  };
}

#endif
