#include "Orwell.h"
#include "Simulation/Pathfinding/AStar.h"

namespace SimulationAStarTest {
  using namespace Orwell::Assertions;
  using namespace Simulation;

  void testBasics() {
    Map map;
    MapFieldType o = MapFieldType::Grass;
    MapFieldType x = MapFieldType::Rock;
    MapFieldType fields[] = {
      o, o, x, o,
      o, x, o, o,
      o, o, o, o
    };
    map.reset(4, 3, fields);

    MapFieldCoors origin = { 3, 0 };
    MapFieldCoors destination = { 1, 0 };
    MapSearchResult result;
    aStar(map, origin, destination, result);

    assertTrue(result.success);
  }

  void setup() {
    unsigned group = Orwell::createGroup("SimulationAStarTest");
    Orwell::addTest(group, testBasics, "Basics");
  }
}
