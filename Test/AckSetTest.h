#include "Orwell.h"
#include "Common/Piper/AckSet.h"

namespace AckSetTest {
  using namespace Orwell::Assertions;
  using namespace Piper;

  void testBasic() {
    AckSet set;
    set.ack(3);
    set.ack(5);
    set.ack(2);

    assertTrue(set.getStatus(2) == AckStatus::Yes);
    assertTrue(set.getStatus(3) == AckStatus::Yes);
    assertTrue(set.getStatus(5) == AckStatus::Yes);
    assertTrue(set.getStatus(4) == AckStatus::No);
    assertTrue(set.getStatus(6) == AckStatus::No);
  }

  void testDouble() {
    AckSet set;
    set.ack(3);
    set.ack(3);
    set.ack(3);

    assertTrue(set.getStatus(2) == AckStatus::No);
    assertTrue(set.getStatus(3) == AckStatus::Yes);
    assertTrue(set.getStatus(5) == AckStatus::No);
  }

  void testScroll() {
    AckSet set;
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
    AckSet set;
    set.ack(0);
    set.ack(500);
    assertTrue(set.getStatus(0) == AckStatus::Unknown);
    assertTrue(set.getStatus(500) == AckStatus::Yes);
    assertTrue(set.getStatus(500-127) == AckStatus::No);
  }

  void testWrapAround() {
    AckSet set;
    set.ack(30);
    set.ack(SEQUENCE_MAX-3);
    set.ack(7);
    assertTrue(set.getStatus(SEQUENCE_MAX-3) == AckStatus::Yes);
    assertTrue(set.getStatus(7) == AckStatus::Yes);
    assertTrue(set.getStatus(1) == AckStatus::No);
    assertTrue(set.getStatus(8) == AckStatus::No);
    assertTrue(set.getStatus(SEQUENCE_MAX-300) == AckStatus::Unknown);

    uint8_t totalYes = 0;
    for(uint8_t i=0; i<128; i++) {
      if(set.getStatus(static_cast<Sequence>(7)-i) == AckStatus::Yes) {
        totalYes++;
      }
    }
    assertEqual(2, totalYes);
  }

  void setup() {
    unsigned suite = Orwell::createSuite("AckSetTest");
    Orwell::addTest(suite, testBasic, "Basic");
    Orwell::addTest(suite, testDouble, "Double");
    Orwell::addTest(suite, testScroll, "Scroll");
    Orwell::addTest(suite, testLargeJump, "LargeJump");
    Orwell::addTest(suite, testWrapAround, "WrapAround");
  }
}
