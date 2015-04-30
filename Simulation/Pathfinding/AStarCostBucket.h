#ifndef SIMULATION_ASTAR_COST_BUCKET_H
#define SIMULATION_ASTAR_COST_BUCKET_H

#include "Simulation/Config.h"
#include "Fixie/Num.h"
#include "Simulation/Pathfinding/MapNodeIndex.h"

namespace Simulation {
  class AStarCostBucket {
  public:
    void add(MapNodeIndex mapNodeIndex, Fixie::Num cost);
    bool get(MapNodeIndex mapNodeIndex, Fixie::Num &cost) const;
    void clear();
  private:
    static const uint32_t max = Config::mapSizeMax/Config::aStarCostBucketCount;
    MapNodeIndex nodes[max];
    Fixie::Num costs[max];
    uint16_t count = 0;
  };
}

#endif
