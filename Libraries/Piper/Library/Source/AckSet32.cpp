#include "Piper/Util.h"
#include "Piper/AckSet32.h"

namespace Piper {
  void AckSet32::ack(Sequence id) {
    if(Util::sequenceGreaterThan(head-32, id)) {
      return;
    }
    else if(id == head) {
      return;
    }
    if(Util::sequenceGreaterThan(id, head+32)) {
      head = id;
      bits.clear();
    }
    else if(Util::sequenceGreaterThan(id, head)) {
      bits.left(id-head);
      bits.set(id-head-1);
      head = id;
    } else {
      bits.set(head-id-1);
    }
  }

  const BitSet32& AckSet32::getBits() const {
    return bits;
  }

  Sequence AckSet32::getHead() const {
    return head;
  }
}
