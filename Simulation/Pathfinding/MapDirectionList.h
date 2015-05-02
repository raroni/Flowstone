#ifndef SIMULATION_MAP_DIRECTION_LIST_H
#define SIMULATION_MAP_DIRECTION_LIST_H

#include "Fixie/Num.h"
#include "Simulation/Pathfinding/MapFieldIndex.h"

namespace Simulation {
  class MapDirectionList {
  public:
    void clear();
    void add(MapFieldIndex destination, Fixie::Num cost);
    static const uint8_t max = 8;
    uint8_t count = 0;
    MapFieldIndex destinations[max];
    Fixie::Num costs[max];
  };
}

#endif
