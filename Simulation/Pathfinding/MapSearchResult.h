#ifndef SIMULATION_MAP_SEARCH_RESULT_H
#define SIMULATION_MAP_SEARCH_RESULT_H

namespace Simulation {
  struct MapSearchResult {
    bool success = false;
    uint16_t count = 0;
    void reset() {
      success = false;
      count = 0;
    }
  };
}

#endif
