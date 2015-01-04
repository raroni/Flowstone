#include <stdlib.h>

namespace Quanta {
  float lerp(float a, float b, float progress) {
    return a + (b-a)*progress;
  }

  float random() {
    return static_cast<float>(rand())/RAND_MAX;
  }
}
