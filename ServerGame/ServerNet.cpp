#include <assert.h>
#include "Common/Piper/Config.h"
#include "Common/Piper/Server.h"
#include "ServerGame/ServerNet.h"

namespace ServerNet {
  static const uint8_t max = 8;
  Piper::Server pipe;
  bool idLookup[Piper::Config::Server::clientMax] = { false };
  uint8_t indices[Piper::Config::Server::clientMax];
  Piper::ClientID ids[max];
  uint8_t sendCounts[max];
  uint8_t count = 0;

  void createClient(Piper::ClientID id) {
    // todo: better handling, rejection of some kind
    assert(count != max);

    idLookup[id] = true;
    indices[id] = count;
    ids[count] = id;
    sendCounts[count] = 0;
    count++;
  }

  void listen(const Piper::Address &address) {
    pipe.listen(address);
  }

  bool readMessage(Piper::ClientID *id, MessageType *type, const void **message, uint16_t *messageLength) {
    bool result = pipe.readMessage(id, message, messageLength);

    if(result) {
      *messageLength = (*messageLength)-1;
      *type = *static_cast<const MessageType*>(*message);
      *message = static_cast<const char*>(*message)+1;
      if(!idLookup[*id]) {
        createClient(*id);
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
