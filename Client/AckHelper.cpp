#include "Net.h"
#include "AckHelper.h"

namespace Client {
  namespace AckHelper {
    bool received = false;
    bool sent = false;
    bool reliableTypes[static_cast<unsigned>(MessageType::Count)] = { false };

    void initialize() {
      reliableTypes[static_cast<unsigned>(MessageType::Test)] = true;
    }

    void handleReceive(MessageType type) {
      if(reliableTypes[static_cast<unsigned>(type)]) {
        received = true;
      }
    }

    void handleSend() {
      sent = true;
    }

    void check() {
      if(received && !sent) {
        Net::sendMessage(0, 0);
      }
      sent = false;
      received = false;
    }
  }
}
