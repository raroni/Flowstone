#ifndef SIMULATION_BASE_H
#define SIMULATION_BASE_H

#include "Simulation/CommandList.h"
#include "Simulation/PlayerHandle.h"

namespace Simulation {
  namespace Base {
    PlayerHandle createPlayer();
    void start();
    void stop();
    void tick(const CommandList &commands);
    uint16_t getFrame();
  }
}

#endif
