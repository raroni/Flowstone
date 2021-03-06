#include "Misc/Error.h"
#include "Simulation/ModeName.h"
#include "Simulation/Mode.h"
#include "Simulation/Session.h"

namespace Simulation {
  namespace Session {
    uint16_t frame = 0;
    Mode mode;

    PlayerHandle createPlayer() {
      // todo: fix me!
      return 0;
    }

    void start() {
      mode = playMode;
      mode.enter();
    }

    void stop() {
      mode.exit();
    }

    void tick(const CommandList &commands) {
      if(mode.getTransition() != ModeName::None) {
        switch(mode.getTransition()) {
          // todo: handle transitions here
          default: {
            fatalError("Unknown transition.");
            break;
          }
        }
      }
      mode.tick(commands);
      frame++;
    }

    uint16_t getFrame() {
      return frame;
    }
  }
}
