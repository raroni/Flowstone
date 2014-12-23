#include <assert.h>
#include "Rendering/CullResult.h"

namespace Rendering {
  void CullResult::clear() {
    count = 0;
  }

  void CullResult::addIndex(uint16_t index) {
    indices[count++] = index;
  }

  void CullResult::storeRange(CullGroupIndex group, uint16_t start, uint16_t end) {
    ranges[group].start = start;
    ranges[group].end = end;
  }

  const CullResultRange& CullResult::getRange(CullGroupIndex group) const {
    return ranges[group];
  }
}
