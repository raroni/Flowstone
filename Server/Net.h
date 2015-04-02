#ifndef SERVER_NET_H
#define SERVER_NET_H

#include "Common/MessageType.h"
#include "Common/Piper/Address.h"
#include "Common/Piper/Sequence.h"
#include "Common/Piper/AckStatus.h"
#include "Server/ClientID.h"

namespace Server {
  namespace Net {
    void initialize();
    void listen(const Piper::Address &address);
    bool readMessage(ClientID *id, MessageType *type, const void **message, uint16_t *messageLength);
    Piper::Sequence sendMessage(ClientID clientID, const void *message, uint16_t messageLength);
    void dispatch();
    void poll();
    void clear();
    Piper::AckStatus getStatus(ClientID clientID, Piper::Sequence sequenceID);
    uint8_t getClientCount();
    ClientID getClientID(uint8_t index);
    uint8_t getSendCount(uint8_t index);
  }
}

#endif
