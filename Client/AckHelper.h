#ifndef CLIENT_ACK_HELPER_H
#define CLIENT_ACK_HELPER_H

#include "Misc/MessageType.h"

namespace Client {
  namespace AckHelper {
    void initialize();
    void handleReceive(MessageType type);
    void handleSend();
    void check();
    void clearReceptions();
  }
}

#endif
