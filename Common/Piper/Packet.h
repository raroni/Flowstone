#ifndef PIPER_PACKET_H
#define PIPER_PACKET_H

#include "Conrad/BitSet32.h"
#include "Common/Piper/Address.h"
#include "Common/Piper/Sequence.h"

namespace Piper {
  struct Packet {
    Address address;
    Sequence id;
    Sequence ackHead;
    BitSet32 ackBits;
    const void *message;
    uint16_t messageLength;
  };
}

#endif
