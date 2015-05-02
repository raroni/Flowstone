#include "Simulation/Pathfinding/AStarCostBucket.h"

namespace Simulation {
  void AStarCostBucket::add(MapFieldIndex field, Fixie::Num cost) {
    uint16_t index;
    bool found = false;
    for(index=0; index<count; ++index) {
      if(fields[index] == field) {
        found = true;
        break;
      }
    }

    if(!found) {
      assert(count != max);
      index = count++;
    }
    fields[index] = field;
    costs[index] = cost;
  }

  bool AStarCostBucket::get(MapFieldIndex field, Fixie::Num &cost) const {
    for(uint16_t i=0; i<count; ++i) {
      if(field == fields[i]) {
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
