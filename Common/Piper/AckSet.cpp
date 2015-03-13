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
      head = id;
      bits.clear();
    }
    else if(Util::sequenceGreaterThan(id, head)) {
      Sequence difference = id-head;
      bits.left(difference);
      bits.set(id-head-1);
      head = id;
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
    return head-id-1;
  }
}
