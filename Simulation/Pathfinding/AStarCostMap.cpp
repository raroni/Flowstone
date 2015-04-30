#include "Simulation/Pathfinding/AStarCostMap.h"

namespace Simulation {
  void AStarCostMap::set(MapNodeIndex node, Fixie::Num cost) {
    uint16_t bucketIndex = calcBucketIndex(node);
    buckets[bucketIndex].add(node, cost);
  }

  bool AStarCostMap::get(MapNodeIndex node, Fixie::Num &cost) const {
    const AStarCostBucket &bucket = buckets[calcBucketIndex(node)];
    return bucket.get(node, cost);
  }

  void AStarCostMap::clear() {
    for(uint16_t i=0; i<Config::aStarCostBucketCount; ++i) {
      buckets[i].clear();
    }
  }

  uint16_t AStarCostMap::calcBucketIndex(MapNodeIndex nodeIndex) const {
    return nodeIndex % Config::aStarCostBucketCount;
  }
}
