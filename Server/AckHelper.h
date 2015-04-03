#ifndef SERVER_ACK_HELPER_H
#define SERVER_ACK_HELPER_H

#include "Common/MessageType.h"
#include "Server/ClientID.h"

namespace Server {
  namespace AckHelper {
    void initialize();
    void handleReceive(ClientID id, MessageType type);
    void check();
  }
}

#endif
