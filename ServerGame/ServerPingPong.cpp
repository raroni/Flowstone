#include <string.h>
#include "Common/MessageType.h"
#include "ServerGame/ServerNet.h"
#include "ServerPingPong.h"

namespace ServerPingPong {
  void handlePing(Piper::ClientID clientID, uint8_t pingID) {
    char message[2];
    message[0] = static_cast<char>(MessageType::Pong);
    memcpy(message+1, &pingID, 1);
    ServerNet::sendMessage(clientID, message, sizeof(message));
  }

  void update(double timeDelta) {
    /*
    for(uint8_t i=0; i<pipe->getClientCount(); ++i) {
      // what to do?
    }
    */
  }
}
