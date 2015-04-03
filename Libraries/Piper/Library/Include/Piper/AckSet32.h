#ifndef PIPER_ACK_SET_32_H
#define PIPER_ACK_SET_32_H

#include "Conrad/BitSet32.h"
#include "Piper/AckStatus.h"
#include "Piper/Sequence.h"

namespace Piper {
  class AckSet32 {
  public:
    void ack(Sequence id);
    Sequence getHead() const;
    const BitSet32& getBits() const;
  private:
    Sequence head = SEQUENCE_MAX-32;
    BitSet32 bits;
  };
}

#endif
