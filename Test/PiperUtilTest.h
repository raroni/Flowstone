#include "Piper/Util.h"

namespace PiperUtilTest {
  using namespace Orwell::Assertions;
  using namespace Piper;

  void testSequenceGreaterThan() {
    assertFalse(Util::sequenceGreaterThan(5, 5));
    assertFalse(Util::sequenceGreaterThan(5, 100));
    assertTrue(Util::sequenceGreaterThan(100, 5));

    assertTrue(Util::sequenceGreaterThan(5, SEQUENCE_MAX));
    assertFalse(Util::sequenceGreaterThan(SEQUENCE_MAX, 5));

    assertTrue(Util::sequenceGreaterThan(0, SEQUENCE_MAX));

    assertTrue(Util::sequenceGreaterThan(100, 50000));
    assertFalse(Util::sequenceGreaterThan(50000, 100));

    Sequence almostMax = SEQUENCE_MAX-5;
    assertTrue(Util::sequenceGreaterThan(5, almostMax));
    assertFalse(Util::sequenceGreaterThan(almostMax, 5));
  }

  void setup() {
    unsigned suite = Orwell::createSuite("PiperUtil");
    Orwell::addTest(suite, testSequenceGreaterThan, "SequenceGreaterThan");
  }
}
