#ifndef SERVER_ACK_HELPER_H
#define SERVER_ACK_HELPER_H

#include "Common/Piper/ClientID.h"
#include "Common/MessageType.h"

namespace ServerAckHelper {
  void handleReceive(Piper::ClientID id, MessageType type);
  void check();
}

#endif
