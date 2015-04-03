#include "Piper/Client.h"
#include "AckHelper.h"
#include "Net.h"

namespace Client {
  namespace Net {
    Piper::Client pipe;

    void initialize() {
      AckHelper::initialize();
    }

    void setAddress(Piper::Address address) {
      pipe.setAddress(address);
    }

    void poll() {
      pipe.poll();
    }

    void clear() {
      pipe.clear();
    }

    bool readMessage(MessageType *type, const void **message, uint16_t *messageLength) {
      bool result = pipe.readMessage(message, messageLength);
      if(result) {
        *messageLength = (*messageLength)-1;
        *type = *static_cast<const MessageType*>(*message);
        *message = static_cast<const char*>(*message)+1;
        AckHelper::handleReceive(*type);
      }
      return result;
    }

    Piper::Sequence sendMessage(const void *message, uint16_t messageLength) {
      AckHelper::handleSend();
      return pipe.sendMessage(message, messageLength);
    }

    void dispatch() {
      AckHelper::check();
      pipe.dispatch();
    }

    Piper::AckStatus getStatus(Piper::Sequence id) {
      return pipe.getStatus(id);
    }
  }
}
