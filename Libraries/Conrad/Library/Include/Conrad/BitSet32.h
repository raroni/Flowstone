#ifndef CONRAD_BIT_SET32_H
#define CONRAD_BIT_SET32_H

#include <stdint.h>

class BitSet32 {
public:
  void set(uint8_t n) {
    data |= 1 << n;
  }
  bool get(uint8_t n) const {
    return (data >> n) & 1;
  }
  void unset(uint8_t n) {
    data &= ~(1 << n);
  }
private:
  uint32_t data = 0;
};

#endif