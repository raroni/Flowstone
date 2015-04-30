#include "Misc/Util.h"
#include "Simulation/Pathfinding/MapNeighbourIterator.h"

namespace Simulation {
  MapNeighbourIterator::MapNeighbourIterator(MapArea mapSize, MapFieldCoors origin) {
    upperLeft.x = Util::maxInt32(0, static_cast<int32_t>(origin.x)-1);
    upperLeft.y = Util::maxInt32(0, static_cast<int32_t>(origin.y)-1);
    lowerRight.x = Util::minInt32(mapSize.width-1, static_cast<int32_t>(origin.x)+1);
    lowerRight.y = Util::minInt32(mapSize.height-1, static_cast<int32_t>(origin.y)+1);
    current = upperLeft;
  }

  MapFieldCoors MapNeighbourIterator::get() {
    return current;
  }

  void MapNeighbourIterator::next() {
    current.y++;
    if(current.y > lowerRight.y) {
      current.y = upperLeft.y;
      current.x++;
    }
  }

  bool MapNeighbourIterator::isEmpty() {
    return (
      current.x > lowerRight.x
    );
  }
}
