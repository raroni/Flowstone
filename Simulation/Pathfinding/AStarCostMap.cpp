#include "Simulation/Pathfinding/AStarCostMap.h"

namespace Simulation {
  void AStarCostMap::set(MapFieldIndex field, Fixie::Num cost) {
    uint16_t bucketIndex = calcBucketIndex(field);
    buckets[bucketIndex].add(field, cost);
  }

  bool AStarCostMap::get(MapFieldIndex field, Fixie::Num &cost) const {
    const AStarCostBucket &bucket = buckets[calcBucketIndex(field)];
    return bucket.get(field, cost);
  }

  void AStarCostMap::clear() {
    for(uint16_t i=0; i<Config::aStarCostBucketCount; ++i) {
      buckets[i].clear();
    }
  }

  uint16_t AStarCostMap::calcBucketIndex(MapFieldIndex fieldIndex) const {
    return fieldIndex % Config::aStarCostBucketCount;
  }
}
