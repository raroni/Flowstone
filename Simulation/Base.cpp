#include "Simulation/Base.h"

namespace Simulation {
  namespace Base {
    uint16_t frame = 0;

    PlayerID createPlayer() {
      // todo: fix me!
      return 0;
    }

    void start() {

    }

    void tick(const CommandList &commands) {
      // do stuff

      frame++;
    }

    uint16_t getFrame() {
      return frame;
    }
  }
}
