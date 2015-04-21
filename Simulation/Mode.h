#ifndef SIMULATION_MODE_H
#define SIMULATION_MODE_H

#include "Simulation/ModeName.h"
#include "Simulation/EventList.h"
#include "Simulation/CommandList.h"

namespace Simulation {
  struct Mode {
    void (*enter)();
    void (*tick)(const CommandList &commands, EventList &events);
    void (*exit)();
    ModeName (*getTransition)();
  };

  extern const Mode playMode;
}

#endif
