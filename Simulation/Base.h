#ifndef SIMULATION_BASE_H
#define SIMULATION_BASE_H

#include "Simulation/PlayerID.h"

namespace Simulation {
  namespace Base {
    PlayerID createPlayer();
    void start();
    void tick();
    uint16_t getFrame();
  }
}

#endif
