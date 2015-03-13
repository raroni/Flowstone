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
    assertTrue(bits.get(30));
    assertTrue(bits.get(29));
    assertFalse(bits.get(1));
    assertFalse(bits.get(2));
    assertFalse(bits.get(3));
    assertFalse(bits.get(28));
    assertFalse(bits.get(31));
  }

  void setup() {
    //unsigned suite = Orwell::createSuite("AckSet32Test");
    //Orwell::addTest(suite, testBasic, "Basic");
  }
}
