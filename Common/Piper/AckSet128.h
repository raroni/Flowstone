#ifndef PIPER_ACK_SET_128_H
#define PIPER_ACK_SET_128_H

#include "Conrad/BitSet128.h"
#include "Common/Piper/AckStatus.h"
#include "Common/Piper/Sequence.h"

namespace Piper {
  class AckSet128 {
  public:
    void ack(Sequence id);
    AckStatus getStatus(Sequence id) const;
    Sequence getHead() const;
    const BitSet128& getBits() const;
  private:
    uint8_t getBitIndex(Sequence id) const;
    Sequence head = SEQUENCE_MAX-128;
    BitSet128 bits;
  };
}

#endif
