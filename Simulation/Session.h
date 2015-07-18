#ifndef SIMULATION_SESSION_H
#define SIMULATION_SESSION_H

#include "Simulation/CommandList.h"
#include "Simulation/PlayerHandle.h"

namespace Simulation {
  namespace Session {
    PlayerHandle createPlayer();
    void start();
    void stop();
    void tick(const CommandList &commands);
    uint16_t getFrame();
  }
}

#endif
