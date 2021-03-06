#ifndef CLIENT_LOCAL_SIMULATION_DRIVER_H
#define CLIENT_LOCAL_SIMULATION_DRIVER_H

#include "Client/CommandList.h"
#include "Simulation/CommandList.h"

namespace Client {
  namespace LocalSimulationTicker {
    void update(
      Simulation::PlayerHandle playerID,
      double timeDelta,
      const CommandList &clientCommands,
      Simulation::CommandList &simulationCommands
    );
  }
}

#endif
