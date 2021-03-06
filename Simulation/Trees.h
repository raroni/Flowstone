#ifndef SIMULATION_TREES_H
#define SIMULATION_TREES_H

#include <stdint.h>

namespace Simulation {
  namespace Trees {
    void initialize();
    void create(uint16_t x, uint16_t z);
    void update();
  }
}

#endif
