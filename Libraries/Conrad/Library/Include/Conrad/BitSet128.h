#ifndef CONRAD_BIT_SET128_H
#define CONRAD_BIT_SET128_H

#include <stdint.h>

class BitSet128 {
public:
  void set(uint8_t n) {
    data[n/8] |= 1 << (n % 8);
  }
  bool get(uint8_t n) const {
    return (data[n/8] >> (n % 8)) & 1;
  }
  void unset(uint8_t n) {
    data[n/8] &= ~(1 << (n % 8));
  }
private:
  uint8_t data[16] = { 0 };
};

#endif
