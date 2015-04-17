#ifndef SIMULATION_PLAY_MODE_H
#define SIMULATION_PLAY_MODE_H

#include "Simulation/ModeName.h"
#include "Simulation/CommandList.h"

namespace Simulation {
  namespace PlayMode {
    void enter();
    void tick(const CommandList &commands);
    void exit();
    ModeName getTransition();
  }
}

#endif
