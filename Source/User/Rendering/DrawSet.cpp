#include "Rendering/DrawSet.h"

namespace Rendering {
  void DrawSet::clear() {
    staticSet.count = 0;
    boneSet.count = 0;
  }
}
