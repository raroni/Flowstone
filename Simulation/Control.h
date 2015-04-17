#ifndef SIMULATION_CONTROL_H
#define SIMULATION_CONTROL_H

#include "Simulation/CommandList.h"
#include "Simulation/EventList.h"
#include "Simulation/PlayerHandle.h"

namespace Simulation {
  namespace Control {
    PlayerHandle createPlayer();
    void start();
    void stop();
    void tick(const CommandList &commands, EventList &events);
    uint16_t getFrame();
  }
}

#endif
