#include "Simulation/AStarPriorityQueueTest.h"
#include "Simulation/AStarCostMapTest.h"
#include "Simulation/MapTest.h"
#include "Simulation/AStarTest.h"
#include "Simulation/MapNeighbourIteratorTest.h"

namespace SimulationTestSuite {
  void setup() {
    SimulationAStarPriorityQueueTest::setup();
    SimulationAStarCostMapTest::setup();
    SimulationMapTest::setup();
    SimulationAStarTest::setup();
    SimulationMapNeighbourIteratorTest::setup();
  }
}
