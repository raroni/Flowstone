#ifndef SIMULATION_PLAY_MODE_H
#define SIMULATION_PLAY_MODE_H

#include "Simulation/ModeName.h"
#include "Simulation/CommandList.h"
#include "Simulation/EventList.h"

namespace Simulation {
  namespace PlayMode {
    void enter();
    void tick(const CommandList &commands, EventList &events);
    void exit();
    ModeName getTransition();
  }
}

#endif
