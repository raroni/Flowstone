#ifndef SIMULATION_INPUT_LIST_H
#define SIMULATION_INPUT_LIST_H

#include <stdint.h>
#include "Simulation/PlayerHandle.h"

namespace Simulation {
  class CommandList {
  public:
    void writeTestCommand(PlayerHandle player, uint8_t x);
    void clear();
    uint8_t getCount() const;
  private:
    static const uint16_t bufferCapacity = 10*1024;
    char buffer[bufferCapacity];
    uint8_t count = 0;
  };
}

#endif
