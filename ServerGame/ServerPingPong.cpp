#include <string.h>
#include "Common/MessageType.h"
#include "ServerPingPong.h"

#include <stdio.h>

namespace ServerPingPong {
  static Piper::Server *pipe;
  static Piper::Sequence *nextSequenceID;

  void configure(Piper::Server *aPipe, Piper::Sequence *aNextSequenceID) {
    pipe = aPipe;
    nextSequenceID = aNextSequenceID;
  }

  void handlePing(Piper::ClientID clientID, uint8_t pingID) {
    char message[2];
    message[0] = static_cast<char>(MessageType::Pong);
    memcpy(message+1, &pingID, 1);
    pipe->sendMessage(
      clientID,
      pipe->createSequenceID(clientID),
      message,
      sizeof(message)
    );
  }

  void update(double timeDelta) {
    /*
    for(uint8_t i=0; i<pipe->getClientCount(); ++i) {
      // what to do?
    }
    */
  }
}
