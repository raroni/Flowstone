#include "Orwell.h"
#include "Simulation/Pathfinding/AStarPriorityQueue.h"

namespace SimulationAStarPriorityQueueTest {
  using namespace Orwell::Assertions;
  using namespace Simulation;

  void testBasics() {
    AStarPriorityQueue queue;
    queue.insert(6, 7.2);
    queue.insert(4, 5.2);
    assertFalse(queue.isEmpty());
    assertEqual(4, queue.pop());
    assertEqual(6, queue.pop());
    assertTrue(queue.isEmpty());
  }

  void testEvenInserts() {
    AStarPriorityQueue queue;
    queue.insert(1, 7);
    queue.insert(2, 13);
    queue.insert(3, 1.2);
    queue.insert(4, 0.5);
    queue.insert(5, 20);
    queue.insert(6, 3);

    assertFalse(queue.isEmpty());
    assertEqual(4, queue.pop());
    assertEqual(3, queue.pop());
    assertEqual(6, queue.pop());
    assertEqual(1, queue.pop());
    assertEqual(2, queue.pop());
    assertFalse(queue.isEmpty());
    assertEqual(5, queue.pop());
    assertTrue(queue.isEmpty());
  }

  void testOddInserts() {
    AStarPriorityQueue queue;
    queue.insert(1, 7);
    queue.insert(2, 13);
    queue.insert(3, 1.2);
    queue.insert(4, 0.5);
    queue.insert(5, 20);
    queue.insert(6, 3);
    queue.insert(7, 0.1);

    assertEqual(7, queue.pop());
    assertEqual(4, queue.pop());
    assertEqual(3, queue.pop());
    assertEqual(6, queue.pop());
    assertEqual(1, queue.pop());
    assertEqual(2, queue.pop());
    assertEqual(5, queue.pop());
    assertTrue(queue.isEmpty());
  }

  void testInterleavedInsertsPops() {
    AStarPriorityQueue queue;
    queue.insert(1, 25);
    queue.insert(2, 13);

    assertEqual(2, queue.pop());

    queue.insert(3, 6);
    queue.insert(4, 2);
    queue.insert(5, 12);

    assertEqual(4, queue.pop());
    assertEqual(3, queue.pop());

    queue.insert(6, 15);
    queue.insert(7, 14);
    queue.insert(8, 13);
    queue.insert(9, 19);

    assertEqual(5, queue.pop());
    assertEqual(8, queue.pop());
    assertEqual(7, queue.pop());
    assertEqual(6, queue.pop());
    assertEqual(9, queue.pop());
    assertEqual(1, queue.pop());
    assertTrue(queue.isEmpty());
  }

  void testEqualPriorities() {
    AStarPriorityQueue queue;
    MapFieldIndex result;
    queue.insert(1, 2);
    queue.insert(2, 3);
    queue.insert(3, 2);
    queue.insert(4, 3);
    queue.insert(5, 1);

    assertFalse(queue.isEmpty());
    assertEqual(5, queue.pop());

    result = queue.pop();
    assertTrue(result == 1 || result == 3);
    result = queue.pop();
    assertTrue(result == 1 || result == 3);

    result = queue.pop();
    assertTrue(result == 2 || result == 4);
    result = queue.pop();
    assertTrue(result == 2 || result == 4);

    assertTrue(queue.isEmpty());
  }

  void testClear() {
    AStarPriorityQueue queue;
    queue.insert(1, 2);
    queue.insert(2, 3);
    queue.clear();
    assertTrue(queue.isEmpty());
  }

  void testUpdateIncrease() {
    AStarPriorityQueue queue;
    queue.insert(1, 10);
    queue.insert(2, 15);
    queue.insert(3, 20);

    queue.update(1, 30);

    assertEqual(2, queue.pop());
    assertEqual(3, queue.pop());
    assertEqual(1, queue.pop());
  }

  void testUpdateDecrease() {
    AStarPriorityQueue queue;
    queue.insert(1, 10);
    queue.insert(2, 15);
    queue.insert(3, 20);

    queue.update(2, 5);

    assertEqual(2, queue.pop());
    assertEqual(1, queue.pop());
    assertEqual(3, queue.pop());
  }

  void setup() {
    unsigned group = Orwell::createGroup("SimulationAStarPriorityQueue");
    Orwell::addTest(group, testBasics, "Basics");
    Orwell::addTest(group, testEvenInserts, "EvenInserst");
    Orwell::addTest(group, testOddInserts, "OddInserst");
    Orwell::addTest(group, testInterleavedInsertsPops, "InterleavedInsertsPops");
    Orwell::addTest(group, testEqualPriorities, "EqualPriorities");
    Orwell::addTest(group, testClear, "Clear");
    Orwell::addTest(group, testUpdateIncrease, "UpdateIncrease");
    Orwell::addTest(group, testUpdateDecrease, "UpdateDecrease");
  }
}
