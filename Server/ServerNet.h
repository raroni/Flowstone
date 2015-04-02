#ifndef SERVER_NET_H
#define SERVER_NET_H

#include "Common/MessageType.h"
#include "Common/Piper/Address.h"
#include "Common/Piper/Sequence.h"
#include "Common/Piper/AckStatus.h"
#include "Server/ServerGameClientID.h"

namespace ServerNet {
  void initialize();
  void listen(const Piper::Address &address);
  bool readMessage(ServerGameClientID *id, MessageType *type, const void **message, uint16_t *messageLength);
  Piper::Sequence sendMessage(ServerGameClientID clientID, const void *message, uint16_t messageLength);
  void dispatch();
  void poll();
  void clear();
  Piper::AckStatus getStatus(ServerGameClientID clientID, Piper::Sequence sequenceID);
  uint8_t getClientCount();
  ServerGameClientID getClientID(uint8_t index);
  uint8_t getSendCount(uint8_t index);
}

#endif
