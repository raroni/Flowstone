#include "Orwell.h"
#include "Conrad/BitSet32.h"

namespace BitSet32Test {
  using namespace Orwell::Assertions;

  void testInitialState() {
    BitSet32 bits;
    for(uint8_t i=0; i<32; ++i) {
      assertFalse(bits.get(i));
    }
  }

  void testSetGet() {
    BitSet32 bits;
    bits.set(6);
    bits.set(14);
    bits.set(31);

    assertFalse(bits.get(0));
    assertFalse(bits.get(5));
    assertFalse(bits.get(7));
    assertFalse(bits.get(27));

    assertTrue(bits.get(6));
    assertTrue(bits.get(14));
    assertTrue(bits.get(31));

    uint8_t totalSet = 0;
    for(uint8_t i=0; i<32; ++i) {
      if(bits.get(i)) {
       totalSet++;
      }
    }
    assertEqual(3, totalSet);
  }

  void testUnset() {
    BitSet32 bits;
    bits.set(6);
    bits.set(7);
    bits.unset(6);

    assertFalse(bits.get(6));
    assertTrue(bits.get(7));
  }

  void testClear() {
    BitSet32 bits;
    bits.set(6);
    bits.set(7);
    bits.clear();

    uint8_t total = 0;
    for(uint8_t i=0; i<32; ++i) {
      total += bits.get(i);
    }
    assertEqual(0, total);
  }

  void testLeft() {
    BitSet32 bits;
    bits.set(3);
    bits.set(5);
    bits.set(10);
    bits.set(30);
    bits.left(4);

    uint8_t total = 0;
    for(uint8_t i=0; i<32; ++i) {
      total += bits.get(i);
    }
    assertEqual(3, total);
    assertTrue(bits.get(7));
    assertTrue(bits.get(9));
    assertTrue(bits.get(14));
  }

  void setup() {
    unsigned group = Orwell::createGroup("BitSet32");
    Orwell::addTest(group, testInitialState, "InitialState");
    Orwell::addTest(group, testSetGet, "SetGet");
    Orwell::addTest(group, testUnset, "Unset");
    Orwell::addTest(group, testClear, "Clear");
    Orwell::addTest(group, testLeft, "Left");
  }
}
