#include <assert.h>
#include "Piper/Server.h"
#include "Server/ClientSet.h"
#include "Server/AckHelper.h"
#include "Server/Net.h"

namespace Server {
  namespace Net {
    Piper::Server pipe;

    void initialize() {
      AckHelper::initialize();
    }

    void listen(const Piper::Address &address) {
      pipe.listen(address);
    }

    bool readMessage(ClientID *id, MessageType *type, const void **message, uint16_t *messageLength) {
      Piper::ClientID piperID;
      bool result = pipe.readMessage(&piperID, message, messageLength);

      if(result) {
        *messageLength = (*messageLength)-1;
        *type = *static_cast<const MessageType*>(*message);
        *message = static_cast<const char*>(*message)+1;

        // todo: handle client overflow
        if(!ClientSet::locatePiperID(piperID)) {
          ClientSet::create(piperID);
        }

        *id = ClientSet::findIDByPiperID(piperID);
        AckHelper::handleReceive(*id, *type);
      }

      return result;
    }

    Piper::Sequence sendMessage(ClientID clientID, const void *message, uint16_t messageLength) {
      const uint8_t *indices = ClientSet::indices;
      uint8_t *sendCounts = ClientSet::sendCounts;
      const Piper::ClientID *piperIDs = ClientSet::piperIDs;

      uint8_t index = indices[clientID];
      assert(sendCounts[index] != UINT8_MAX);
      sendCounts[index]++;
      Piper::ClientID piperID = piperIDs[index];
      return pipe.sendMessage(piperID, message, messageLength);
    }

    Piper::AckStatus getStatus(ClientID clientID, Piper::Sequence sequenceID) {
      uint8_t index = ClientSet::indices[clientID];
      Piper::ClientID piperID = ClientSet::piperIDs[index];
      return pipe.getStatus(piperID, sequenceID);
    }

    void dispatch() {
      AckHelper::check();
      pipe.dispatch();
      ClientSet::clearSendCounts();
    }

    void poll() {
      pipe.poll();
    }

    void clear() {
      pipe.clear();
    }
  }
}
