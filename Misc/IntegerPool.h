#ifndef INTEGER_POOL_H
#define INTEGER_POOL_H

#include <stdint.h>

class IntegerPool {
public:
  uint16_t obtain();
  void release(uint16_t value);
private:
  uint16_t max = 0;
  static const uint16_t recycleMax = 256;
  uint16_t recycles[recycleMax];
  uint16_t recycleCount = 0;
};

#endif
