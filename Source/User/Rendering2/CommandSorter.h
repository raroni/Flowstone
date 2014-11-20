#ifndef RENDERING2_COMMAND_SORTER_H
#define RENDERING2_COMMAND_SORTER_H

#include <assert.h>
#include <string.h>
#include <algorithm>
#include "Rendering2/Config.h"
#include "Rendering2/CommandType.h"
#include "Rendering2/CommandWriter.h"

namespace Rendering2 {
  union OrderKey {
    uint32_t integer;
    struct {
      uint32_t layer : 4;
      // other order params
    };
  };

  struct OrderRecord {
    OrderKey key;
    uint16_t offset;
  };

  static inline bool compareOrderRecords(const OrderRecord &a, const OrderRecord &b) {
    return a.key.integer < b.key.integer;
  }

  class CommandSorter {
    char buffer[Config::commandBufferSize];
    CommandWriter writer;
    static const uint16_t maxOrderRecords = 512;
    OrderRecord orderRecords[maxOrderRecords] = {};
    uint16_t count = 0;
    void writeType(CommandType type, OrderKey key) {
      OrderRecord &record = orderRecords[count];
      record.key = key;
      record.offset = writer.getPosition();
      count++;
      writer.writeType(type);
    }
  public:
    CommandSorter() : writer(buffer) { }
    void writeChangeShaderProgram(ChangeShaderProgramCommand command, OrderKey key) {
      writeType(CommandType::ChangeShaderProgram, key);
      writer.writeChangeShaderProgram(command);
    }
    void writeDrawAnimatedMesh(DrawAnimatedMeshCommand command, OrderKey key) {
      writeType(CommandType::DrawAnimatedMesh, key);
      writer.writeDrawAnimatedMesh(command);
    }
    void writeUpdateWorldViewTransform(UpdateWorldViewTransformCommand command, OrderKey key) {
      writeType(CommandType::UpdateWorldViewTransform, key);
      writer.writeUpdateWorldViewTransform(command);
    }
    void sort() {
      std::sort(orderRecords, orderRecords+count, compareOrderRecords);
    }
    uint16_t getCount() const {
      return count;
    }
    const char* get(uint16_t position) const {
      const OrderRecord &record = orderRecords[position];
      return buffer+record.offset;
    }
    void clear() {
      count = 0;
      writer.reset();
    }
  };
}

#endif
