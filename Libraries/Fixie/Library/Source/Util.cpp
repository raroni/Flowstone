#include <assert.h>
#include "Fixie/Config.h"
#include "Fixie/Util.h"

namespace Fixie {
  namespace Util {
    static const int32_t floorMask = (~0) << Config::numPrecision;

    Num zero(0);

    Num halve(Num n) {
      return Num::createByRaw(n.raw >> 1);
    }

    Num floor(Num n) {
      n.raw &= floorMask;
      return n;
    }

    Num sqrt(Num n) {
      assert(n >= Num(0));
      Num s = halve(n);
      for(uint8_t i=0; i<8 && s != zero; ++i) {
        s = halve(s + n/s);
      }
      return s;
    }
  }
}
