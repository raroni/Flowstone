#ifndef CLIENT_ACK_HELPER_H
#define CLIENT_ACK_HELPER_H

#include "Common/MessageType.h"

namespace ClientAckHelper {
  void initialize();
  void handleReceive(MessageType type);
  void handleSend();
  void check();
  void clearReceptions();
}

#endif
