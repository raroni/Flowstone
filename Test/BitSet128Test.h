#include "Orwell.h"
#include "Conrad/BitSet128.h"

namespace BitSet128Test {
  using namespace Orwell::Assertions;

  void testInitialState() {
    BitSet128 bits;
    for(uint8_t i=0; i<128; ++i) {
      assertFalse(bits.get(i));
    }
  }

  void testSetGet() {
    BitSet128 bits;
    bits.set(6);
    bits.set(37);
    bits.set(124);

    assertFalse(bits.get(0));
    assertFalse(bits.get(5));
    assertFalse(bits.get(7));
    assertFalse(bits.get(127));

    assertTrue(bits.get(6));
    assertTrue(bits.get(37));
    assertTrue(bits.get(124));

    uint8_t totalSet = 0;
    for(uint8_t i=0; i<128; ++i) {
      if(bits.get(i)) {
        totalSet++;
      }
    }
    assertEqual(3, totalSet);
  }

  void testUnset() {
    BitSet128 bits;
    bits.set(6);
    bits.set(7);
    bits.unset(6);

    assertFalse(bits.get(6));
    assertTrue(bits.get(7));
  }

  void testClear() {
    BitSet128 bits;
    bits.set(6);
    bits.set(7);
    bits.set(46);
    bits.clear();

    for(uint8_t i=0; i<128; ++i) {
      assertFalse(bits.get(i));
    }
  }

  void testLeft() {
    BitSet128 bits;
    bits.set(3);
    bits.set(5);
    bits.set(80);
    bits.set(126);
    bits.left(4);

    uint8_t total = 0;
    for(uint8_t i=0; i<128; ++i) {
      total += bits.get(i);
    }
    assertEqual(3, total);
    assertTrue(bits.get(7));
    assertTrue(bits.get(9));
    assertTrue(bits.get(84));
  }

  void setup() {
    unsigned suite = Orwell::createSuite("BitSet128");
    Orwell::addTest(suite, testInitialState, "InitialState");
    Orwell::addTest(suite, testSetGet, "SetGet");
    Orwell::addTest(suite, testUnset, "Unset");
    Orwell::addTest(suite, testClear, "Clear");
    Orwell::addTest(suite, testLeft, "Left");
  }
}
