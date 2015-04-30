#ifndef SIMULATION_ASTAR_COST_MAP_H
#define SIMULATION_ASTAR_COST_MAP_H

#include "Simulation/Config.h"
#include "Simulation/Pathfinding/AStarCostBucket.h"

namespace Simulation {
  class AStarCostMap {
  public:
    void set(MapNodeIndex node, Fixie::Num cost);
    bool get(MapNodeIndex node, Fixie::Num &cost) const;
    void clear();
  private:
    uint16_t calcBucketIndex(MapNodeIndex node) const;
    AStarCostBucket buckets[Config::aStarCostBucketCount];
  };
}

#endif
