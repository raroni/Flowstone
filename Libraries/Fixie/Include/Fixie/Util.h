#ifndef FIXIE_UTIL_H
#define FIXIE_UTIL_H

namespace Fixie {
  namespace Util {
    Num floor(Num n) {
      n.raw &= 0xfffffc00;
      return n;
    }

    Num fmod(Num a, Num b) {
      Num q = floor(a/b);
      return a-q*b;
    }
  }
}

#endif
