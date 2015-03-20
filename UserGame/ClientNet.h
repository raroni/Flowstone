#ifndef CLIENT_NET_H
#define CLIENT_NET_H

#include "Common/Piper/Address.h"
#include "Common/Piper/Sequence.h"
#include "Common/Piper/AckStatus.h"

namespace ClientNet {
  void setAddress(Piper::Address address);
  void poll();
  void clear();
  bool readMessage(const void **message, uint16_t *messageLength);
  Piper::Sequence sendMessage(const void *message, uint16_t messageLength);
  void dispatch();
  Piper::AckStatus getStatus(Piper::Sequence id);
}

#endif
