#include <string.h>
#include "Server/Config.h"
#include "Server/ClientSet.h"
#include "Server/Net.h"
#include "Server/AckHelper.h"

namespace Server {
  namespace AckHelper {
    bool reliableReceived[Config::clientMax] = { false };
    bool reliableTypes[static_cast<unsigned>(MessageType::Count)] = { false };

    void initialize() {
      reliableTypes[static_cast<unsigned>(MessageType::Test)] = true;
    }

    void handleReceive(ClientID id, MessageType type) {
      if(reliableTypes[static_cast<unsigned>(type)]) {
        reliableReceived[id] = true;
      }
    }

    void check() {
      uint8_t count = ClientSet::getCount();
      const ClientID *ids = ClientSet::ids;
      const uint8_t *sendCounts = ClientSet::sendCounts;

      for(uint8_t i=0; i<count; ++i) {
        ClientID id = ids[i];
        if(reliableReceived[id] && sendCounts[i] == 0) {
          Net::sendMessage(id, 0, 0);
        }
      }
      memset(reliableReceived, false, sizeof(reliableReceived));
    }
  }
}
