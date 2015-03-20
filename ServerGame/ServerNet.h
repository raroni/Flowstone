#ifndef SERVER_NET_H
#define SERVER_NET_H

#include "Common/Piper/Address.h"
#include "Common/Piper/ClientID.h"
#include "Common/Piper/Sequence.h"

namespace ServerNet {
  void listen(const Piper::Address &address);
  bool readMessage(Piper::ClientID *id, const void **message, uint16_t *messageLength);
  Piper::Sequence sendMessage(Piper::ClientID clientID, const void *message, uint16_t messageLength);
  void dispatch();
  void poll();
  void clear();
}

#endif
