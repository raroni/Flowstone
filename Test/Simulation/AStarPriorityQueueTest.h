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

  void testRandomChallenge1() {
    AStarPriorityQueue queue;

    queue.insert(23, 0.000000);
    queue.pop();
    queue.insert(6, 10.414185);
    queue.insert(22, 9.000000);
    queue.insert(38, 8.414185);
    queue.insert(7, 11.000000);
    queue.insert(39, 9.000000);
    queue.insert(8, 12.414185);
    queue.insert(24, 11.000000);
    queue.insert(40, 10.414185);

    assertEqual(38, queue.pop());

    Fixie::Num x = queue.pop();
    assertTrue(x == Fixie::Num(39) || x == Fixie::Num(22));
    x = queue.pop();
    assertTrue(x == Fixie::Num(39) || x == Fixie::Num(22));

    x = queue.pop();
    assertTrue(x == Fixie::Num(40) || x == Fixie::Num(6));
    x = queue.pop();
    assertTrue(x == Fixie::Num(40) || x == Fixie::Num(6));

    x = queue.pop();
    assertTrue(x == Fixie::Num(24) || x == Fixie::Num(7));
    x = queue.pop();
    assertTrue(x == Fixie::Num(24) || x == Fixie::Num(7));

    assertEqual(8, queue.pop());
  }

  void testRandomChallenge2() {
    AStarPriorityQueue queue;
    queue.insert(17, 0.000000);
    queue.pop();
    queue.insert(6, 10.414185);
    queue.insert(16, 9.000000);
    queue.insert(26, 8.414185);
    queue.insert(7, 11.000000);
    queue.insert(27, 9.000000);
    queue.insert(8, 12.414185);
    queue.insert(18, 11.000000);
    queue.insert(28, 10.414185);
    queue.pop();
    queue.insert(15, 9.828369);
    queue.insert(25, 8.414185);
    queue.insert(35, 7.828369);
    queue.insert(36, 8.414185);
    queue.insert(37, 9.828369);


    assertEqual(35, queue.pop());
    assertEqual(25, queue.pop());
    assertEqual(36, queue.pop());

    Fixie::Num x = queue.pop();
    assertTrue(x == Fixie::Num(16) || x == Fixie::Num(27));
    x = queue.pop();
    assertTrue(x == Fixie::Num(16) || x == Fixie::Num(27));

    x = queue.pop();
    assertTrue(x == Fixie::Num(15) || x == Fixie::Num(37));
    x = queue.pop();
    assertTrue(x == Fixie::Num(15) || x == Fixie::Num(37));

    x = queue.pop();
    assertTrue(x == Fixie::Num(6) || x == Fixie::Num(28));
    x = queue.pop();
    assertTrue(x == Fixie::Num(6) || x == Fixie::Num(28));

    x = queue.pop();
    assertTrue(x == Fixie::Num(7) || x == Fixie::Num(18));
    x = queue.pop();
    assertTrue(x == Fixie::Num(7) || x == Fixie::Num(18));

    assertEqual(8, queue.pop());
  }

  void testRandomChallenge3() {
    AStarPriorityQueue queue;

    queue.insert(10, 1);
    queue.insert(11, 2);
    queue.insert(12, 3);
    queue.insert(13, 4);
    queue.insert(14, 5);

    assertEqual(10, queue.pop());
    assertEqual(11, queue.pop());
    assertEqual(12, queue.pop());
    assertEqual(13, queue.pop());
    assertEqual(14, queue.pop());
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
    Orwell::addTest(group, testRandomChallenge1, "RandomChallenge1");
    Orwell::addTest(group, testRandomChallenge2, "RandomChallenge2");
    Orwell::addTest(group, testRandomChallenge3, "RandomChallenge3");
  }
}
