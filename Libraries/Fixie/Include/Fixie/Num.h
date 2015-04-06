#ifndef FIXIE_NUM_H
#define FIXIE_NUM_H

#include <stdint.h>
#include "Fixie/Config.h"

#include <stdio.h>

namespace Fixie {
  using namespace Config;

  class Num {
  public:
    int32_t raw;
    Num() { }
    Num(int32_t x) {
      raw = x << fractionBits;
    }
    Num(double x) {
      raw = x * (1 << fractionBits);
    }
    Num& operator/=(const Num &rhs) {
      raw = (static_cast<uint64_t>(raw) << fractionBits) / rhs.raw;
      return *this;
    }
    Num& operator*=(const Num &rhs) {
      raw = (static_cast<uint64_t>(raw) << fractionBits) / rhs.raw;
      return *this;
    }
    Num operator%(Num rhs) {
      Num result = *this / rhs;
      result.raw &= 0x3ff;
      return result;
    }
    operator float() const {
      return static_cast<float>(raw) / (1 << fractionBits);
    }
    static Num createByRaw(int32_t raw) {
      Num n;
      n.raw = raw;
      return n;
    }
  };
}

#endif
