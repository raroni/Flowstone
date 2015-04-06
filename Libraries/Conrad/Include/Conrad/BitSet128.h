#ifndef CONRAD_BIT_SET128_H
#define CONRAD_BIT_SET128_H

#include <stdint.h>
#include <string.h>

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
  void clear() {
    memset(data, 0, sizeof(data));
  }
  void left(uint8_t n) {
    uint64_t *uint64View = reinterpret_cast<uint64_t*>(data);
    uint64View[0] <<= n;
    uint64View[0] |= uint64View[1] >> n & ((1 << (n+1))-1);
    uint64View[1] <<= n;
  }
private:
  uint8_t data[16] = { 0 };
};

#endif
