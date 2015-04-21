#include "Simulation/CommandList.h"

namespace Simulation {
  void CommandList::writeTestCommand(PlayerHandle player, uint8_t x) {
    count++;
  }

  void CommandList::clear() {
    count = 0;
  }

  uint8_t CommandList::getCount() const {
    return count;
  }
}
