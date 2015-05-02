#include "Orwell.h"
#include "Misc/IntegerPool.h"

namespace IntegerPoolTest {
  using namespace Orwell::Assertions;

  void testBasics() {
    IntegerPool pool;
    assertEqual(0, pool.obtain());
    assertEqual(1, pool.obtain());
    assertEqual(2, pool.obtain());
    assertEqual(3, pool.obtain());
    assertEqual(4, pool.obtain());
    pool.release(3);
    pool.release(1);
    assertEqual(1, pool.obtain());
    assertEqual(3, pool.obtain());
    assertEqual(5, pool.obtain());
    assertEqual(6, pool.obtain());
    pool.release(0);
    assertEqual(0, pool.obtain());
    assertEqual(7, pool.obtain());
  }

  void setup() {
    unsigned group = Orwell::createGroup("IntegerPool");
    Orwell::addTest(group, testBasics, "Basics");
  }
}
