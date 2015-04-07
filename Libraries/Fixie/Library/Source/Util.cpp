#include "Fixie/Util.h"

namespace Fixie {
  namespace Util {
    Num floor(Num n) {
      n.raw &= 0xfffffc00;
      return n;
    }
  }
}
