#ifndef SIMULATION_MAP_SEARCH_RESULT_H
#define SIMULATION_MAP_SEARCH_RESULT_H

#include "Simulation/Config.h"

namespace Simulation {
  struct MapSearchResult {
    bool success = false;
    uint16_t count = 0;
    MapFieldCoors path[Config::mapSizeMax];
    void reset() {
      success = false;
      count = 0;
    }
    void add(MapFieldCoors coors) {
      path[count++] = coors;
    }
  };
}

#endif
