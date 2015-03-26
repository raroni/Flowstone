#include "Orwell.h"
#include "Common/Piper/AckSet32.h"

namespace AckSet32Test {
  using namespace Orwell::Assertions;
  using namespace Piper;

  void testBasic() {
    AckSet32 acks;
    acks.ack(3);
    acks.ack(5);
    acks.ack(2);

    assertEqual(5, acks.getHead());

    const BitSet32 &bits = acks.getBits();
    assertTrue(bits.get(2));
    assertTrue(bits.get(1));
    assertFalse(bits.get(0));
    assertFalse(bits.get(3));
    assertFalse(bits.get(4));
    assertFalse(bits.get(28));
    assertFalse(bits.get(31));
  }

  void testLatecomers() {
    AckSet32 acks;
    acks.ack(60);
    acks.ack(3);

    uint8_t totalOn = 0;
    for(uint8_t i=0; i<=32; i++) {
      if(acks.getBits().get(i)) {
        totalOn++;
      }
    }
    assertEqual(0, totalOn);
  }

  void testDouble() {
    AckSet32 acks;
    acks.ack(3);
    acks.ack(5);
    acks.ack(5);
    acks.ack(8);
    acks.ack(8);

    assertEqual(8, acks.getHead());

    const BitSet32 &bits = acks.getBits();
    assertTrue(bits.get(2));
    assertTrue(bits.get(4));
    assertFalse(bits.get(0));
    assertFalse(bits.get(1));
    assertFalse(bits.get(3));
    assertFalse(bits.get(5));
  }

  void testLargeJump() {
    AckSet32 acks;
    acks.ack(0);
    acks.ack(70);

    assertEqual(70, acks.getHead());
    uint8_t totalOn = 0;
    for(uint8_t i=0; i<=32; i++) {
      if(acks.getBits().get(i)) {
        totalOn++;
      }
    }
    assertEqual(0, totalOn);
  }

  void testInitialState() {
    AckSet32 acks;
    assertEqual(SEQUENCE_MAX-32, acks.getHead());
    uint8_t totalOn = 0;
    for(uint8_t i=0; i<=32; i++) {
      if(acks.getBits().get(i)) {
        totalOn++;
      }
    }
    assertEqual(0, totalOn);
  }

  void testWrapAround() {
    AckSet32 acks;
    Sequence quarter = SEQUENCE_MAX/4;
    acks.ack(30);
    acks.ack(quarter);
    acks.ack(quarter*2);
    acks.ack(quarter*3);
    acks.ack(SEQUENCE_MAX-3);
    acks.ack(2);

    assertEqual(2, acks.getHead());

    const BitSet32 &bits = acks.getBits();
    assertTrue(bits.get(5));
    assertFalse(bits.get(1));
    assertFalse(bits.get(2));
    assertFalse(bits.get(3));
    assertFalse(bits.get(4));
    assertFalse(bits.get(6));
    assertFalse(bits.get(7));
  }

  void testGetHead() {
    AckSet32 acks;

    acks.ack(30);
    assertEqual(30, acks.getHead());

    acks.ack(29);
    assertEqual(30, acks.getHead());

    acks.ack(31);
    assertEqual(31, acks.getHead());

    acks.ack(100);
    assertEqual(100, acks.getHead());
  }

  void testAckZero() {
    AckSet32 set;
    set.ack(0);

    assertEqual(0, set.getHead());

    const BitSet32 &bits = set.getBits();
    uint8_t totalUnset = 0;
    for(uint8_t i=0; i<32; i++) {
      totalUnset += bits.get(i);
    }
    assertEqual(0, totalUnset);
  }

  void setup() {
    unsigned suite = Orwell::createSuite("AckSet32Test");
    Orwell::addTest(suite, testBasic, "Basic");
    Orwell::addTest(suite, testLatecomers, "Latecomers");
    Orwell::addTest(suite, testDouble, "Double");
    Orwell::addTest(suite, testLargeJump, "largeJump");
    Orwell::addTest(suite, testInitialState, "InitialState");
    Orwell::addTest(suite, testWrapAround, "WrapAround");
    Orwell::addTest(suite, testGetHead, "GetHead");
    Orwell::addTest(suite, testAckZero, "AckZero");
  }
}
