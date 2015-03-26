#ifndef SERVER_ACK_HELPER_H
#define SERVER_ACK_HELPER_H

#include "Common/MessageType.h"
#include "ServerGameClientID.h"

namespace ServerAckHelper {
  void initialize();
  void handleReceive(ServerGameClientID id, MessageType type);
  void check();
}

#endif
