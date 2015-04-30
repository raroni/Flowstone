#ifndef SIMULATION_MAP_NEIGHBOUR_ITERATOR_H
#define SIMULATION_MAP_NEIGHBOUR_ITERATOR_H

#include "Simulation/Pathfinding/Map.h"

namespace Simulation {
  class MapNeighbourIterator {
  public:
    MapNeighbourIterator(Map &map, MapFieldCoors origin);
    MapFieldCoors get();
    void next();
    bool isEmpty();
  private:
    MapFieldCoors upperLeft;
    MapFieldCoors lowerRight;
    MapFieldCoors current;
  };
}

#endif
