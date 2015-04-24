#ifndef SIMULATION_DRAG_SYSTEM_H
#define SIMULATION_DRAG_SYSTEM_H

#include "Simulation/Drag/DragHandle.h"

namespace Simulation {
  namespace DragSystem {
    DragHandle create(Physics::ForceDriverHandle handle);
    void update();
  }
}

#endif
