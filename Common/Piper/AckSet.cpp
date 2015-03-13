#include "Common/Piper/Util.h"
#include "Common/Piper/AckSet.h"

namespace Piper {
  void AckSet::ack(Sequence id) {
    Sequence difference = id-base;
    if(difference > 255) {
      position = 0;
      base = id-127;
      bits.clear();
    }
    else if(difference > 127) {
      Sequence steps = difference-127;
      uint8_t bitIndex = getBitIndex(base);
      for(uint8_t i=0; i<steps; ++i) {
        bits.unset(bitIndex+i);
      }
      position = (position+steps) % 128;
      base = id-127;
    }
    bits.set(getBitIndex(id));
  }

  AckStatus AckSet::getStatus(Sequence id) {
    if(Util::sequenceGreaterThan(base, id)) {
      return AckStatus::Unknown;
    } else {
      Sequence difference = id-base;
      if(difference > 127 || !bits.get(getBitIndex(id))) {
        return AckStatus::No;
      } else {
        return AckStatus::Yes;
      }
    }
  }

  uint8_t AckSet::getBitIndex(Sequence id) {
    Sequence difference = id-base;
    return static_cast<uint8_t>(difference+position) % 128;
  }
}