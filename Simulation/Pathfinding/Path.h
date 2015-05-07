#ifndef SIMULATION_PATH_H
#define SIMULATION_PATH_H

#include <assert.h>
#include "Fixie/Vector2.h"

namespace Simulation {
  struct Path {
    uint16_t count = 0;
    uint16_t nextWaypointIndex = 0;
    const static uint16_t waypointMax = 1024;
    Fixie::Vector2 waypoints[Config::mapSizeMax];
    void reset() {
      nextWaypointIndex = 0;
      count = 0;
    }
    void add(Fixie::Vector2 waypoint) {
      assert(waypointMax != count);
      waypoints[count++] = waypoint;
    }
  };
}

#endif
