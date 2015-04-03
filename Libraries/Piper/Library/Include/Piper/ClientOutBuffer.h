#ifndef PIPER_CLIENT_OUT_BUFFER_H
#define PIPER_CLIENT_OUT_BUFFER_H

#include <stdint.h>
#include "Piper/Config.h"
#include "Piper/Sequence.h"
#include "Piper/MessageBuffer.h"

namespace Piper {
  class ClientOutBuffer {
  public:
    ClientOutBuffer();
    void write(Sequence id, const void *message, uint16_t messageLength);
    uint16_t read(uint16_t position, Sequence *id, const void **message);
    uint16_t getCount() const;
    void clear();
  private:
    Sequence ids[Config::Client::outMessageMax];
    uint16_t offsets[Config::Client::outMessageMax];
    uint16_t lengths[Config::Client::outMessageMax];
    char storage[Config::Client::outMessageCapacity];
    MessageBuffer messages;
  };
}

#endif
