#ifndef SIMULATION_INPUT_LIST_H
#define SIMULATION_INPUT_LIST_H

#include <stdint.h>

namespace Simulation {
  class CommandList {
  public:
    void writeCreatePlayerCommand();
    void clear();
  private:
    static const uint16_t bufferCapacity = 10*1024;
    char buffer[bufferCapacity];
  };
}

#endif
