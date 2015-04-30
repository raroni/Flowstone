#ifndef UTIL_H
#define UTIL_H

namespace Util {
  int32_t minInt32(int32_t a, int32_t b) {
    if(a < b) {
      return a;
    } else {
      return b;
    }
  }

  int32_t maxInt32(int32_t a, int32_t b) {
    if(a > b) {
      return a;
    } else {
      return b;
    }
  }
}

#endif
