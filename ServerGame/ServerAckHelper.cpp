#include <string.h>
#include "ServerGame/ServerGameConfig.h"
#include "ServerGame/ServerNet.h"
#include "ServerGame/ServerAckHelper.h"

namespace ServerAckHelper {
  bool reliableReceived[ServerGameConfig::clientMax] = { false };
  bool reliableTypes[static_cast<unsigned>(MessageType::Count)] = { false };

  void initialize() {
    reliableTypes[static_cast<unsigned>(MessageType::Test)] = true;
  }

  void handleReceive(ServerGameClientID id, MessageType type) {
    if(reliableTypes[static_cast<unsigned>(type)]) {
      reliableReceived[id] = true;
    }
  }

  void check() {
    for(uint8_t i=0; i<ServerNet::getClientCount(); ++i) {
      ServerGameClientID id = ServerNet::getClientID(i);
      uint8_t sendCount = ServerNet::getSendCount(i);
      if(reliableReceived[id] && sendCount == 0) {
        ServerNet::sendMessage(id, 0, 0);
      }
    }
    memset(reliableReceived, false, sizeof(reliableReceived));
  }
}
