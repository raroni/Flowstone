#include "Common/Piper/Util.h"
#include "Common/Piper/AckSet32.h"

namespace Piper {
  void AckSet32::ack(Sequence id) {
    Sequence tail = head-32;
    if(Util::sequenceGreaterThan(tail, id)) {
      return;
    }
    else if(id == head) {
      return;
    }
    if(Util::sequenceGreaterThan(id, head+128)) {
      head = id;
      // not impl yet
    }
    else if(Util::sequenceGreaterThan(id, head)) {
      head = id;
      // not impl yet
      //bits.left(difference);
    } else {
      // bits.set(id);
    }
  }

  const BitSet32& AckSet32::getBits() const {
    return bits;
  }

  Sequence AckSet32::getHead() const {
    return head;
  }
}
