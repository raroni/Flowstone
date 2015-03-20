#include "Common/Piper/Server.h"
#include "ServerGame/ServerNet.h"

namespace ServerNet {
  Piper::Server pipe;

  void listen(const Piper::Address &address) {
    pipe.listen(address);
  }

  bool readMessage(Piper::ClientID *id, const void **message, uint16_t *messageLength) {
    return pipe.readMessage(id, message, messageLength);
  }

  Piper::Sequence sendMessage(Piper::ClientID clientID, const void *message, uint16_t messageLength) {
    return pipe.sendMessage(clientID, message, messageLength);
  }

  void dispatch() {
    pipe.dispatch();
  }

  void poll() {
    pipe.poll();
  }

  void clear() {
    pipe.clear();
  }
}
