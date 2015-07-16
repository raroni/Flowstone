#ifndef SIMULATION_MODE_H
#define SIMULATION_MODE_H

#include "Simulation/ModeName.h"
#include "Simulation/CommandList.h"

namespace Simulation {
  struct Mode {
    void (*enter)();
    void (*tick)(const CommandList &commands);
    void (*exit)();
    ModeName (*getTransition)();
  };

  extern const Mode playMode;
}

#endif
