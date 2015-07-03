#include "Simulation/Harvest/HarvestEventList.h"

namespace Simulation {
  namespace HarvestEventList {
    const uint16_t max = 64;
    uint16_t count = 0;
    HarvestEvent events[max];

    uint16_t getCount() {
      return count;
    }

    void clear() {
      count = 0;
    }

    const HarvestEvent* get(uint16_t index) {
      return &events[index];
    }
  }
}
