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

  void setup() {
    unsigned suite = Orwell::createSuite("BitSet32");
    Orwell::addTest(suite, testInitialState, "InitialState");
    Orwell::addTest(suite, testSetGet, "SetGet");
    Orwell::addTest(suite, testUnset, "Unset");
    Orwell::addTest(suite, testClear, "Clear");
  }
}
