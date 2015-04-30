#include "Simulation/AStarPriorityQueueTest.h"
#include "Simulation/AStarCostMapTest.h"
#include "Simulation/MapTest.h"

namespace SimulationTestSuite {
  void setup() {
    SimulationAStarPriorityQueueTest::setup();
    SimulationAStarCostMapTest::setup();
    SimulationMapTest::setup();
  }
}
