#include "Orwell.h"
#include "Conrad/BitSet32.h"

namespace LoopStreamTest {
  using namespace Orwell::Assertions;

  void testInitialState() {
    const uint16_t max = 4;
    uint16_t offsets[max] = { 0 };
    uint16_t lengths[max] = { 0 };
    bool existances[max] = { false };
    const uint16_t capacity = 1024*10;
    char buffer[capacity];

    LoopStream stream(offsets, lengths, existances, max, buffer, capacity);
  }

  void setup() {
    unsigned suite = Orwell::createSuite("LoopStream");
    Orwell::addTest(suite, testInitialState, "InitialState");
  }
}
