#include "Common/Piper/Client.h"
#include "ClientNet.h"

namespace ClientNet {
  Piper::Client pipe;

  void setAddress(Piper::Address address) {
    pipe.setAddress(address);
  }

  void poll() {
    pipe.poll();
  }

  void clear() {
    pipe.clear();
  }

  bool readMessage(const void **message, uint16_t *messageLength) {
    return pipe.readMessage(message, messageLength);
  }

  Piper::Sequence sendMessage(const void *message, uint16_t messageLength) {
    return pipe.sendMessage(message, messageLength);
  }

  void dispatch() {
    pipe.dispatch();
  }

  Piper::AckStatus getStatus(Piper::Sequence id) {
    return pipe.getStatus(id);
  }
}
