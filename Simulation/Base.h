#ifndef SIMULATION_BASE_H
#define SIMULATION_BASE_H

#include "Simulation/CommandList.h"
#include "Simulation/EventList.h"
#include "Simulation/PlayerHandle.h"

namespace Simulation {
  namespace Base {
    PlayerHandle createPlayer();
    void start();
    void stop();
    void tick(const CommandList &commands, EventList &events);
    uint16_t getFrame();
  }
}

#endif
