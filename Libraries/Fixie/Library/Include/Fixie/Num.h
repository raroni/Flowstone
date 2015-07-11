#ifndef FIXIE_NUM_H
#define FIXIE_NUM_H

#include <math.h>
#include <stdint.h>
#include <assert.h>
#include "Fixie/Config.h"

namespace Fixie {
  using namespace Config;

  class Num {
  public:
    int32_t raw = 0;
    Num() { }
    Num(int32_t x) {
      raw = x << numPrecision;
    }
    Num(double x) {
      raw = round(x * (1 << numPrecision));
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
      assert(rhs.raw != 0);
      const int32_t resultNegative = ((raw ^ rhs.raw) & 0x80000000) >> 31;
      const int32_t sign = resultNegative*-2+1;
      int64_t temp = static_cast<int64_t>(raw) << numPrecision;
      temp += rhs.raw/2*sign;
      raw = static_cast<int32_t>(temp / rhs.raw);
      return *this;
    }
    Num& operator*=(const Num &rhs) {
      int64_t int64 = (static_cast<int64_t>(raw) * rhs.raw) >> numPrecision;
      raw = static_cast<int32_t>(int64);
      return *this;
    }
    Num operator+(const Num &other) const {
      Num result = *this;
      result += other;
      return result;
    }
    Num operator-(const Num &other) const {
      Num result = *this;
      result -= other;
      return result;
    }
    Num operator*(const Num &other) const {
      Num result = *this;
      result *= other;
      return result;
    }
    Num operator/(const Num &other) const {
      Num result = *this;
      result /= other;
      return result;
    }
    bool operator==(const Num &other) const {
      return raw == other.raw;
    }
    bool operator!=(const Num &other) const {
      return !(*this == other);
    }
    bool operator<(const Num &other) const {
      return raw < other.raw;
    }
    bool operator<=(const Num &other) const {
      return raw <= other.raw;
    }
    bool operator>(const Num &other) const {
      return raw > other.raw;
    }
    bool operator>=(const Num &other) const {
      return raw >= other.raw;
    }
    operator float() const {
      return static_cast<float>(raw) / (1 << numPrecision);
    }
    operator double() const {
      return static_cast<double>(raw) / (1 << numPrecision);
    }
    operator int32_t() const {
      return raw >> numPrecision;
    }
    operator uint16_t() const {
      assert(raw >= 0);
      return raw >> numPrecision;
    }
    static Num createByRaw(int32_t raw) {
      Num n;
      n.raw = raw;
      return n;
    }
    static Num inverse(int32_t n) {
      Num x = 1;
      Num y = n;
      return x/y;
    }
  };
}

#endif
