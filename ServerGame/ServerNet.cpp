#include "Common/Piper/Config.h"
#include "Common/Piper/Server.h"
#include "ServerGame/ServerNet.h"

namespace ServerNet {
  Piper::Server pipe;
  bool clientIDs[Piper::Config::Server::clientMax] = { false };

  void listen(const Piper::Address &address) {
    pipe.listen(address);
  }

  bool readMessage(Piper::ClientID *id, MessageType *type, const void **message, uint16_t *messageLength) {
    bool result = pipe.readMessage(id, message, messageLength);

    if(result) {
      *messageLength = (*messageLength)-1;
      *type = *static_cast<const MessageType*>(*message);
      *message = static_cast<const char*>(*message)+1;
      if(!clientIDs[*id]) {
        clientIDs[*id] = true;
        // zomg new connection
        // put into active players or into rejection-queue (if full)
      }
    }

    return result;
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
