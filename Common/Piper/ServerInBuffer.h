#ifndef PIPER_SERVER_BUFFER_H
#define PIPER_SERVER_BUFFER_H

#include "Common/Piper/MessageBuffer.h"
#include "Common/Piper/ClientID.h"

namespace Piper {
  class ServerInBuffer {
  public:
    ServerInBuffer(
      uint16_t maxCount,
      uint16_t capacity,
      ClientID *ids,
      uint16_t *offsets,
      uint16_t *lengths,
      void *storage
    );
    void write(ClientID id, const void *message, uint16_t messageLength);
    uint16_t read(uint16_t position, ClientID *id, const void **message);
    uint16_t getCount() const;
    void clear();
  private:
    MessageBuffer messages;
    ClientID *ids;
  };
}

#endif
