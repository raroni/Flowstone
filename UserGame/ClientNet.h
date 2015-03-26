#ifndef CLIENT_NET_H
#define CLIENT_NET_H

#include "Common/Piper/Address.h"
#include "Common/Piper/Sequence.h"
#include "Common/Piper/AckStatus.h"
#include "Common/MessageType.h"

namespace ClientNet {
  void initialize();
  void setAddress(Piper::Address address);
  void poll();
  void clear();
  bool readMessage(MessageType *type, const void **message, uint16_t *messageLength);
  Piper::Sequence sendMessage(const void *message, uint16_t messageLength);
  void dispatch();
  Piper::AckStatus getStatus(Piper::Sequence id);
}

#endif
