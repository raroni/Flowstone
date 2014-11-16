#include "Rendering2/Culler.h"

namespace Rendering2 {
  void Culler::create(ObjectIndex index) {
    indices[count++] = index;
  }

  uint16_t Culler::cull(ObjectIndex *result) const {
    // TODO: Make a real impl.
    for(uint16_t i=0; count>i; i++) {
      result[i] = indices[i];
    }
    return count;
  }
}
