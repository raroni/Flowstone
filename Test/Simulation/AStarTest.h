#include "Orwell.h"
#include "Simulation/Pathfinding/AStar.h"

namespace SimulationAStarTest {
  using namespace Orwell::Assertions;
  using namespace Simulation;

  void assertPath(MapSearchResult &result, uint16_t waypointCount, const MapFieldCoors *waypoints) {
    assertEqual(result.count, waypointCount);
    for(uint16_t i=0; i<waypointCount; ++i) {
      assertEqual(waypoints[i].x, result.path[i].x);
      assertEqual(waypoints[i].y, result.path[i].y);
    }
  }

  void testBasics() {
    Map map;
    MapFieldType o = MapFieldType::Grass;
    MapFieldType x = MapFieldType::Tree;
    MapFieldType fields[] = {
      o, o, x, o,
      o, x, o, o,
      o, o, o, o
    };
    map.reset(4, 3, fields);

    MapFieldCoors origin = { 3, 0 };
    MapFieldCoors destination = { 1, 0 };
    MapSearchResult result;
    Fixie::Num tolerance = 0;
    aStar(map, origin, destination, tolerance, result);

    assertTrue(result.success);
    MapFieldCoors waypoints[] = {
      { 3, 1 },
      { 2, 2 },
      { 1, 2 },
      { 0, 2 },
      { 0, 1 },
      { 0, 0 },
      { 1, 0 }
    };
    assertPath(result, sizeof(waypoints)/sizeof(MapFieldCoors), waypoints);
  }

  void testTolerance() {
    Map map;
    MapFieldType o = MapFieldType::Grass;
    MapFieldType x = MapFieldType::Tree;
    MapFieldType fields[] = {
      x, o, o,
      o, o, x,
      o, x, o,
      o, o, o
    };
    map.reset(3, 4, fields);

    MapFieldCoors origin = { 2, 0 };
    MapFieldCoors destination = { 2, 2 };
    MapSearchResult result;
    Fixie::Num tolerance = 1;
    aStar(map, origin, destination, tolerance, result);

    assertTrue(result.success);
    MapFieldCoors waypoints[] = {
      { 1, 0 },
      { 1, 1 },
      { 0, 1 },
      { 0, 2 },
      { 0, 3 },
      { 1, 3 },
      { 2, 3 },
      { 2, 2 }
    };
    assertPath(result, sizeof(waypoints)/sizeof(MapFieldCoors), waypoints);
  }

  void setup() {
    unsigned group = Orwell::createGroup("SimulationAStar");
    Orwell::addTest(group, testBasics, "Basics");
    Orwell::addTest(group, testTolerance, "Tolerance");
  }
}
