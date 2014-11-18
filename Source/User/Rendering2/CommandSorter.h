#ifndef RENDERING2_COMMAND_SORTER_H
#define RENDERING2_COMMAND_SORTER_H

#include <assert.h>
#include <string.h>
#include <algorithm>
#include "Rendering2/Config.h"
#include "Rendering2/CommandType.h"
#include "Rendering2/CommandStream.h"

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
    CommandStream stream;
    static const uint16_t maxOrderRecords = 512;
    OrderRecord orderRecords[maxOrderRecords];
    uint16_t count = 0;
  public:
    void writeType(CommandType type, OrderKey key) {
      OrderRecord record;
      record.key = key;
      record.offset = stream.getPosition();
      orderRecords[count] = record;
      count++;
      stream.writeType(type);
    }
    void writeShaderName(ShaderName name) {
      stream.writeShaderName(name);
    }
    void sort() {
      std::sort(orderRecords, orderRecords+maxOrderRecords, compareOrderRecords);
    }
    uint16_t getCount() const {
      return count;
    }
    const char* get(uint16_t position) const {
      const OrderRecord &record = orderRecords[position];
      return stream.getBuffer()+record.offset;
    }
    void clear() {
      count = 0;
    }
  };
}

#endif
