#include "Orwell.h"
#include "Simulation/Pathfinding/AStarCostMap.h"
#include <stdio.h>

namespace SimulationAStarCostMapTest {
  using namespace Orwell::Assertions;
  using namespace Simulation;

  void assertSuccessfulGet(const AStarCostMap &map, MapNodeIndex node, Fixie::Num inCost) {
    Fixie::Num outCost;
    assert(map.get(node, outCost));
    assertEqual(inCost, outCost);
  }

  void testBasics() {
    AStarCostMap map;
    bool getResult;
    Fixie::Num cost;

    map.set(3, 5);
    assertSuccessfulGet(map, 3, 5);

    getResult = map.get(4, cost);
    assertFalse(getResult);
  }

  void testMany() {
    AStarCostMap map;
    Fixie::Num cost;

    map.set(3, 5);
    map.set(7, 56);
    map.set(9, 4);
    map.set(13, 3.5);
    map.set(20, 2);
    map.set(50, 1);
    map.set(100, 0);

    assertSuccessfulGet(map, 3, 5);
    assertSuccessfulGet(map, 7, 56);
    assertSuccessfulGet(map, 9, 4);
    assertSuccessfulGet(map, 13, 3.5);
    assertSuccessfulGet(map, 20, 2);
    assertSuccessfulGet(map, 50, 1);
    assertSuccessfulGet(map, 100, 0);
  }

  void testOverwrite() {
    AStarCostMap map;
    Fixie::Num cost;

    for(uint16_t i=0; i<4048; ++i) {
      map.set(3, 5);
    }
    assertSuccessfulGet(map, 3, 5);
  }

  void testClear() {
    AStarCostMap map;
    Fixie::Num cost;

    map.set(3, 5);
    map.set(9, 5);
    map.clear();

    assertFalse(map.get(3, cost));
    assertFalse(map.get(9, cost));
  }

  void setup() {
    unsigned group = Orwell::createGroup("AStarCostMapTest");
    Orwell::addTest(group, testBasics, "Basics");
    Orwell::addTest(group, testMany, "Many");
    Orwell::addTest(group, testOverwrite, "Overwrite");
    Orwell::addTest(group, testClear, "Clear");
  }
}
