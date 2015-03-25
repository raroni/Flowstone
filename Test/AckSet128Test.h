#include "Orwell.h"
#include "Common/Piper/AckSet128.h"

namespace AckSet128Test {
  using namespace Orwell::Assertions;
  using namespace Piper;

  void testBasic() {
    AckSet128 set;
    set.ack(3);
    set.ack(5);
    set.ack(2);

    assertTrue(set.getStatus(2) == AckStatus::Yes);
    assertTrue(set.getStatus(3) == AckStatus::Yes);
    assertTrue(set.getStatus(5) == AckStatus::Yes);
    assertTrue(set.getStatus(4) == AckStatus::No);
    assertTrue(set.getStatus(6) == AckStatus::No);
  }

  void testLatecomers() {
    AckSet128 set;
    set.ack(500);
    set.ack(300);

    assertTrue(set.getStatus(500) == AckStatus::Yes);
    assertTrue(set.getStatus(500-128) == AckStatus::No);
    assertTrue(set.getStatus(300) == AckStatus::Unknown);
    assertTrue(set.getStatus(500-129) == AckStatus::Unknown);
  }

  void testRange() {
    AckSet128 set;
    set.ack(200);

    assertTrue(set.getStatus(200-128) == AckStatus::No);
    assertTrue(set.getStatus(200-129) == AckStatus::Unknown);
  }

  void testDouble() {
    AckSet128 set;
    set.ack(3);
    set.ack(3);
    set.ack(3);

    assertTrue(set.getStatus(2) == AckStatus::No);
    assertTrue(set.getStatus(3) == AckStatus::Yes);
    assertTrue(set.getStatus(5) == AckStatus::No);
  }

  void testScroll() {
    AckSet128 set;
    set.ack(130);
    set.ack(135);
    set.ack(134);

    assertTrue(set.getStatus(135-127) == AckStatus::No);
    assertTrue(set.getStatus(130) == AckStatus::Yes);
    assertTrue(set.getStatus(134) == AckStatus::Yes);
    assertTrue(set.getStatus(135) == AckStatus::Yes);
    assertTrue(set.getStatus(1) == AckStatus::Unknown);
    assertTrue(set.getStatus(300) == AckStatus::No);
  }

  void testLargeJump() {
    AckSet128 set;
    set.ack(0);
    set.ack(500);
    assertTrue(set.getStatus(0) == AckStatus::Unknown);
    assertTrue(set.getStatus(500) == AckStatus::Yes);
    assertTrue(set.getStatus(500-127) == AckStatus::No);
  }

  void testWrapAround() {
    AckSet128 set;
    Sequence quarter = SEQUENCE_MAX/4;
    set.ack(30);
    set.ack(quarter);
    set.ack(quarter*2);
    set.ack(quarter*3);
    set.ack(quarter*4-3);
    set.ack(7);

    assertTrue(set.getStatus(quarter*4-3) == AckStatus::Yes);
    assertTrue(set.getStatus(7) == AckStatus::Yes);
    assertTrue(set.getStatus(1) == AckStatus::No);
    assertTrue(set.getStatus(8) == AckStatus::No);
    assertTrue(set.getStatus(SEQUENCE_MAX-300) == AckStatus::Unknown);

    uint8_t totalYes = 0;
    for(uint8_t i=0; i<=128; i++) {
      if(set.getStatus(static_cast<Sequence>(7)-i) == AckStatus::Yes) {
        totalYes++;
      }
    }
    assertEqual(2, totalYes);
  }

  void testGetHead() {
    AckSet128 set;

    assertEqual(SEQUENCE_MAX-128, set.getHead());

    set.ack(5);
    assertEqual(5, set.getHead());

    set.ack(3);
    assertEqual(5, set.getHead());

    set.ack(8);
    assertEqual(8, set.getHead());
  }

  void testGetBits() {
    AckSet128 set;
    set.ack(3);
    set.ack(5);
    set.ack(2);

    const BitSet128& bits = set.getBits();

    uint8_t totalYes = 0;
    for(uint8_t i=0; i<128; i++) {
      totalYes += bits.get(i);
    }
    assertEqual(2, totalYes);

    assertTrue(bits.get(1));
    assertTrue(bits.get(2));
  }

  void testInitialState() {
    AckSet128 set;

    assertEqual(SEQUENCE_MAX-128, set.getHead());

    const BitSet128 &bits = set.getBits();
    uint8_t totalOn = 0;
    for(uint8_t i=0; i<128; i++) {
      totalOn += bits.get(i);
    }
    assertEqual(0, totalOn);

    uint8_t totalNo = 0;
    for(uint8_t i=0; i<128; i++) {
      totalNo += set.getStatus(i) == AckStatus::No;
    }
    assertEqual(128, totalNo);
  }

  void testAckZero() {
    AckSet128 set;
    set.ack(0);

    assertEqual(0, set.getHead());

    uint8_t totalNo = 0;
    for(uint8_t i=1; i<=128; i++) {
      totalNo += set.getStatus(i) == AckStatus::No;
    }
    assertEqual(128, totalNo);
  }

  void setup() {
    unsigned suite = Orwell::createSuite("AckSet128Test");
    Orwell::addTest(suite, testBasic, "Basic");
    Orwell::addTest(suite, testLatecomers, "Latecomers");
    Orwell::addTest(suite, testRange, "Range");
    Orwell::addTest(suite, testDouble, "Double");
    Orwell::addTest(suite, testScroll, "Scroll");
    Orwell::addTest(suite, testLargeJump, "LargeJump");
    Orwell::addTest(suite, testWrapAround, "WrapAround");
    Orwell::addTest(suite, testGetHead, "GetHead");
    Orwell::addTest(suite, testGetBits, "GetBits");
    Orwell::addTest(suite, testInitialState, "InitialState");
    Orwell::addTest(suite, testAckZero, "AckZero");
  }
}
