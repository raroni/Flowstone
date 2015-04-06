#include "Quanta/Random.h"

namespace Quanta {
  Random::Random(unsigned int seed) : engine(seed) { }

  float Random::get() {
    return distribution(engine);
  }
}
