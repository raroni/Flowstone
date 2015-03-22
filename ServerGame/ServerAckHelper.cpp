#include <string.h>
#include "ServerGame/ServerGameConfig.h"
#include "ServerGame/ServerGameClientSet.h"
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
    uint8_t count = ServerGameClientSet::getCount();
    const ServerGameClientID *ids = ServerGameClientSet::ids;
    const uint8_t *sendCounts = ServerGameClientSet::sendCounts;

    for(uint8_t i=0; i<count; ++i) {
      ServerGameClientID id = ids[i];
      if(reliableReceived[id] && sendCounts[i] == 0) {
        ServerNet::sendMessage(id, 0, 0);
      }
    }
    memset(reliableReceived, false, sizeof(reliableReceived));
  }
}
