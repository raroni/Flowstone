#include "Common/Piper/Util.h"
#include "Common/Piper/AckSet.h"

namespace Piper {
  void AckSet::ack(Sequence id) {
    Sequence tail = head-128;
    if(Util::sequenceGreaterThan(tail, id)) {
      return;
    }
    else if(id == head) {
      return;
    }
    if(Util::sequenceGreaterThan(id, head+128)) {
      position = 0;
      head = id;
      bits.clear();
    }
    else if(Util::sequenceGreaterThan(id, head)) {
      Sequence difference = id-head;
      for(uint8_t i=0; i<difference; ++i) {
        bits.unset(getBitIndex(tail+i));
      }
      head = id;
      position = (position+difference) % 128;
      bits.set(getBitIndex(id-difference));
    } else {
      bits.set(getBitIndex(id));
    }
  }

  Sequence AckSet::getHead() const {
    return head;
  }

  AckStatus AckSet::getStatus(Sequence id) {
    if(id == head) {
      return AckStatus::Yes;
    }
    else if(Util::sequenceGreaterThan(head-128, id)) {
      return AckStatus::Unknown;
    }
    else if(
      Util::sequenceGreaterThan(id, head) ||
      !bits.get(getBitIndex(id))
    ) {
      return AckStatus::No;
    }
    return AckStatus::Yes;
  }

  uint8_t AckSet::getBitIndex(Sequence id) {
    Sequence difference = 128-(head-id);
    return static_cast<uint8_t>(difference+position) % 128;
  }
}
