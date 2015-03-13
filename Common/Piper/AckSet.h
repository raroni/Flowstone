#ifndef PIPER_ACK_SET_128_H
#define PIPER_ACK_SET_128_H

#include "Conrad/BitSet128.h"
#include "Common/Piper/AckStatus.h"
#include "Common/Piper/Sequence.h"

namespace Piper {
  class AckSet {
  public:
    void ack(Sequence id);
    AckStatus getStatus(Sequence id);
    uint8_t getBitIndex(Sequence id);
    Sequence getHead() const;
  private:
    Sequence head = SEQUENCE_MAX;
    BitSet128 bits;
  };
}

#endif
