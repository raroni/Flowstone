#include "Misc/Error.h"
#include "Simulation/Config.h"
#include "Simulation/Control.h"
#include "Client/LocalSimulationDriver.h"

namespace Client {
  namespace LocalSimulationDriver {
    static double timeBank = 0;

    void convertCommands(Simulation::PlayerHandle playerID, const CommandList &clientCommands, Simulation::CommandList &simulationCommands) {
      for(uint8_t i=0; i<clientCommands.getCount(); ++i) {
        CommandType type = clientCommands.readType(i);
        switch(type) {
          case CommandType::Test: {
            TestCommand command = clientCommands.readTestCommand(i);
            simulationCommands.writeTestCommand(playerID, command.x);
            break;
          }
          default: {
            fatalError("Unknown command type.");
          }
        }
      }
    }

    void update(
      Simulation::PlayerHandle playerID,
      double timeDelta,
      const CommandList &clientCommands,
      Simulation::CommandList &simulationCommands
    ) {
      convertCommands(playerID, clientCommands, simulationCommands);

      timeBank += timeDelta;
      do {
        Simulation::Control::tick(simulationCommands);
        simulationCommands.clear();
        timeBank -= static_cast<double>(Simulation::Config::tickDuration)/1000;
      } while(timeBank*1000 >= Simulation::Config::tickDuration);
    }
  }
}
