#ifndef FIXIE_NUM_H
#define FIXIE_NUM_H

#include <math.h>
#include <stdint.h>
#include "Fixie/Config.h"

namespace Fixie {
  using namespace Config;

  class Num {
  public:
    int32_t raw = 0;
    Num() { }
    Num(int32_t x) {
      raw = x << fractionBits;
    }
    Num(double x) {
      raw = round(x * (1 << fractionBits));
    }
    Num& operator+=(const Num &rhs) {
      raw += rhs.raw;
      return *this;
    }
    Num& operator-=(const Num &rhs) {
      raw -= rhs.raw;
      return *this;
    }
    Num& operator/=(const Num &rhs) {
      raw = (static_cast<uint64_t>(raw) << fractionBits) / rhs.raw;
      return *this;
    }
    Num& operator*=(const Num &rhs) {
      raw = (static_cast<uint64_t>(raw) * rhs.raw) >> fractionBits;
      return *this;
    }
    Num operator+(const Num &other) {
      Num result = *this;
      result += other;
      return result;
    }
    Num operator-(const Num &other) {
      Num result = *this;
      result -= other;
      return result;
    }
    Num operator*(const Num &other) {
      Num result = *this;
      result *= other;
      return result;
    }
    Num operator/(const Num &other) {
      Num result = *this;
      result /= other;
      return result;
    }
    Num operator%(Num rhs) {
      int32_t a = *this;
      int32_t b = rhs;
      return a % b;
    }
    operator float() const {
      return static_cast<float>(raw) / (1 << fractionBits);
    }
    operator int32_t() const {
      return raw / (1 << fractionBits);
    }
    static Num createByRaw(int32_t raw) {
      Num n;
      n.raw = raw;
      return n;
    }
  };
}

#endif
