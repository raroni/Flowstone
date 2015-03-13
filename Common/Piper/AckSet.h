#ifndef PIPER_ACK_SET_H
#define PIPER_ACK_SET_H

#include "Conrad/BitSet128.h"
#include "Common/Piper/AckStatus.h"
#include "Common/Piper/Sequence.h"

namespace Piper {
  class AckSet {
  public:
    void ack(Sequence id);
    AckStatus getStatus(Sequence id);
    uint8_t getBitIndex(Sequence id);
  private:
    uint8_t position = 0;
    Sequence base = 0;
    BitSet128 bits;
  };
}

#endif
