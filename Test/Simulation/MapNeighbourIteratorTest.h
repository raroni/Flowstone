#include "Orwell.h"
#include "Simulation/Pathfinding/MapNeighbourIterator.h"

namespace SimulationMapNeighbourIteratorTest {
  using namespace Orwell::Assertions;
  using namespace Simulation;

  struct CoordsList {
    MapFieldCoors values[8];
    uint8_t count = 0;
    void add(MapFieldCoors coors) {
      values[count++] = coors;
    }
  };

  void fillList(MapNeighbourIterator &iterator, CoordsList &list) {
    for(;!iterator.isEmpty(); iterator.next()) {
      list.add(iterator.get());
    }
  }

  void testUpperRight() {
    MapFieldCoors coors = { 3, 0 };
    MapArea mapSize = { 4, 3 };
    MapNeighbourIterator iterator(mapSize, coors);
    CoordsList list;
    fillList(iterator, list);

    assertEqual(4, list.count);
  }

  void setup() {
    unsigned group = Orwell::createGroup("SimulationMapNeighbourIterator");
    Orwell::addTest(group, testUpperRight, "testUpperRight");
  }
}
