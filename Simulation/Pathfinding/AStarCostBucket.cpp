#include "Simulation/Pathfinding/AStarCostBucket.h"

namespace Simulation {
  void AStarCostBucket::add(MapNodeIndex node, Fixie::Num cost) {
    uint16_t index;
    bool found = false;
    for(index=0; index<count; ++index) {
      if(nodes[index] == node) {
        found = true;
        break;
      }
    }

    if(!found) {
      assert(count != max);
      index = count++;
    }
    nodes[index] = node;
    costs[index] = cost;
  }

  bool AStarCostBucket::get(MapNodeIndex node, Fixie::Num &cost) const {
    for(uint16_t i=0; i<count; ++i) {
      if(node == nodes[i]) {
        cost = costs[i];
        return true;
      }
    }
    return false;
  }

  void AStarCostBucket::clear() {
    count = 0;
  }
}
