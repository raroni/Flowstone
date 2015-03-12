#include <math.h>
#include "Common/Piper/Util.h"

namespace Piper {
  namespace Util {
    bool sequenceGreaterThan(Sequence a, Sequence b) {
      return (
        (a > b && (a - b <= SEQUENCE_MAX/2)) ||
        (b > a && (b - a > SEQUENCE_MAX/2))
      );
    }
  }
}
