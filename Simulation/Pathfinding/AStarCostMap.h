#ifndef SIMULATION_ASTAR_COST_MAP_H
#define SIMULATION_ASTAR_COST_MAP_H

#include "Simulation/Config.h"
#include "Simulation/Pathfinding/AStarCostBucket.h"

namespace Simulation {
  class AStarCostMap {
  public:
    void set(MapFieldIndex field, Fixie::Num cost);
    bool get(MapFieldIndex field, Fixie::Num &cost) const;
    void clear();
  private:
    uint16_t calcBucketIndex(MapFieldIndex field) const;
    AStarCostBucket buckets[Config::aStarCostBucketCount];
  };
}

#endif
