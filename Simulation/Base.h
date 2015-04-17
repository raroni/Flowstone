#ifndef SIMULATION_BASE_H
#define SIMULATION_BASE_H

#include "Simulation/CommandList.h"
#include "Simulation/PlayerID.h"

namespace Simulation {
  namespace Base {
    PlayerID createPlayer();
    void start();
    void stop();
    void tick(const CommandList &commands);
    uint16_t getFrame();
  }
}

#endif
