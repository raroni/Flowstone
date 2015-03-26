#include "Common/Piper/Client.h"
#include "ClientAckHelper.h"
#include "ClientNet.h"

namespace ClientNet {
  Piper::Client pipe;

  void initialize() {
    ClientAckHelper::initialize();
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
      ClientAckHelper::handleReceive(*type);
    }
    return result;
  }

  Piper::Sequence sendMessage(const void *message, uint16_t messageLength) {
    ClientAckHelper::handleSend();
    return pipe.sendMessage(message, messageLength);
  }

  void dispatch() {
    ClientAckHelper::check();
    pipe.dispatch();
  }

  Piper::AckStatus getStatus(Piper::Sequence id) {
    return pipe.getStatus(id);
  }
}
