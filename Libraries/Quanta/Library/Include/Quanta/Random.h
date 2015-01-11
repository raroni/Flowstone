#ifndef QUANTA_RANDOM_H
#define QUANTA_RANDOM_H

#include <random>

namespace Quanta {
  class Random {
    std::minstd_rand0 engine;
    std::uniform_real_distribution<float> distribution;
  public:
    Random(unsigned int);
    float get();
  };
}

#endif
