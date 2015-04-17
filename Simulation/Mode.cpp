#include "PlayMode.h"
#include "Simulation/Mode.h"

namespace Simulation {
  const Mode playMode = {
    PlayMode::enter,
    PlayMode::tick,
    PlayMode::exit,
    PlayMode::getTransition
  };
}
