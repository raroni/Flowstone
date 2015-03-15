#include "Common/Piper/Util.h"
#include "Common/Piper/AckSet128.h"

namespace Piper {
  void AckSet128::ack(Sequence id) {
    Sequence tail = head-128;
    if(Util::sequenceGreaterThan(tail, id)) {
      return;
    }
    else if(id == head) {
      return;
    }
    if(Util::sequenceGreaterThan(id, head+128)) {
      head = id;
      bits.clear();
    }
    else if(Util::sequenceGreaterThan(id, head)) {
      Sequence difference = id-head;
      bits.left(difference);
      Sequence oldHead = head;
      head = id;
      bits.set(getBitIndex(oldHead));
    } else {
      bits.set(getBitIndex(id));
    }
  }

  AckStatus AckSet128::getStatus(Sequence id) {
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

  uint8_t AckSet128::getBitIndex(Sequence id) {
    return static_cast<Sequence>((head-id-1)) % 128;
  }

  Sequence AckSet128::getHead() const {
    return head;
  }

  const BitSet128& AckSet128::getBits() const {
    return bits;
  }
}
