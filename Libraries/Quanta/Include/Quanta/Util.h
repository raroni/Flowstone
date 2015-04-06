#ifndef QUANTA_UTIL
#define QUANTA_UTIL

namespace Quanta {
  template<typename T> T max(T x, T y) {
    if(x > y) {
      return x;
    } else {
      return y;
    }
  }

  template<typename T> T min(T x, T y) {
    if(x < y) {
      return x;
    } else {
      return y;
    }
  }

  float lerp(float a, float b, float progress);
}

#endif
