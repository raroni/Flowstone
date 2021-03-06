#ifndef CLIENT_NET_H
#define CLIENT_NET_H

#include "Piper/Address.h"
#include "Piper/Sequence.h"
#include "Piper/AckStatus.h"
#include "Misc/MessageType.h"

namespace Client {
  namespace Net {
    void initialize();
    void setAddress(Piper::Address address);
    void poll();
    void clear();
    bool readMessage(MessageType *type, const void **message, uint16_t *messageLength);
    Piper::Sequence sendMessage(const void *message, uint16_t messageLength);
    void dispatch();
    Piper::AckStatus getStatus(Piper::Sequence id);
  }
}

#endif
