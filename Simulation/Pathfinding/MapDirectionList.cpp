#include "Simulation/Pathfinding/MapDirectionList.h"

namespace Simulation {
  void MapDirectionList::clear() {
    count = 0;
  }

  void MapDirectionList::add(MapFieldIndex destination) {
    destinations[count++] = destination;
  }
}
