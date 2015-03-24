#include "Orwell.h"
#include "Common/LoopStream.h"

namespace LoopStreamTest {
  using namespace Orwell::Assertions;

  void testBasic() {
    const uint16_t max = 4;
    uint16_t offsets[max] = { 0 };
    uint16_t lengths[max] = { 0 };
    const uint16_t capacity = 128;
    char buffer[capacity];

    LoopStream stream(offsets, lengths, max, buffer, capacity);
    uint16_t handle;
    assertTrue(stream.write(&handle, "hey", 3));
    void *message = nullptr;
    assertEqual(3, stream.read(handle, &message));
    assertTrue(memcmp("hey", message, 3) == 0);
  }

  void testMax() {
    const uint16_t max = 2;
    uint16_t offsets[max] = { 0 };
    uint16_t lengths[max] = { 0 };
    const uint16_t capacity = 64;
    char buffer[capacity];

    LoopStream stream(offsets, lengths, max, buffer, capacity);
    uint16_t handle;
    assertTrue(stream.write(&handle, "hey", 3));
    assertTrue(stream.write(&handle, "hey", 3));
    assertFalse(stream.write(&handle, "hey", 3));
  }

  void testCapacityOverflow() {
    const uint16_t max = 20;
    uint16_t offsets[max] = { 0 };
    uint16_t lengths[max] = { 0 };
    const uint16_t capacity = 5;
    char buffer[capacity];

    LoopStream stream(offsets, lengths, max, buffer, capacity);
    uint16_t handle;
    assertTrue(stream.write(&handle, "hi", 2));
    assertTrue(stream.write(&handle, "hi", 2));
    assertFalse(stream.write(&handle, "hi", 2));
  }

  void testWrapAround() {
    const uint16_t max = 20;
    uint16_t offsets[max] = { 0 };
    uint16_t lengths[max] = { 0 };
    const uint16_t capacity = 5;
    char buffer[capacity];

    LoopStream stream(offsets, lengths, max, buffer, capacity);
    uint16_t handle1, handle2, handle3;
    assertTrue(stream.write(&handle1, "hi", 2));
    assertTrue(stream.write(&handle2, "hi", 2));
    stream.release(handle1);
    assertTrue(stream.write(&handle3, "hi", 2));
    void *message = nullptr;
    stream.read(handle3, &message);
    assertTrue(message == &buffer);
  }

  void testHoledRelease() {
    const uint16_t max = 20;
    uint16_t offsets[max] = { 0 };
    uint16_t lengths[max] = { 0 };
    const uint16_t capacity = 5;
    char buffer[capacity];

    LoopStream stream(offsets, lengths, max, buffer, capacity);
    uint16_t handle1, handle2, handle3;
    assertTrue(stream.write(&handle1, "hi", 2));
    assertTrue(stream.write(&handle2, "hi", 2));
    stream.release(handle2);
    assertFalse(stream.write(&handle3, "hi", 2));
    stream.release(handle1);
    assertTrue(stream.write(&handle3, "hi", 2));
  }

  void testHoledWrapAroundRelease() {
    const uint16_t max = 20;
    uint16_t offsets[max] = { 0 };
    uint16_t lengths[max] = { 0 };
    const uint16_t capacity = 6;
    char buffer[capacity];

    LoopStream stream(offsets, lengths, max, buffer, capacity);
    uint16_t handleA, handleB, handle;
    assertTrue(stream.write(&handle, "hi", 2));
    stream.release(handle);

    assertTrue(stream.write(&handle, "hi", 2));
    stream.release(handle);

    assertTrue(stream.write(&handleA, "hi", 2));
    assertTrue(stream.write(&handleB, "hi", 2));
    assertFalse(stream.write(&handle, "hi", 2));

    stream.release(handleB);
    assertFalse(stream.write(&handle, "hi", 2));
    stream.release(handleA);
    assertTrue(stream.write(&handle, "hi", 2));
    assertTrue(stream.write(&handle, "hi", 2));
  }

  void setup() {
    unsigned suite = Orwell::createSuite("LoopStream");
    Orwell::addTest(suite, testBasic, "testBasic");
    Orwell::addTest(suite, testMax, "testMax");
    Orwell::addTest(suite, testCapacityOverflow, "testCapacityOverflow");
    Orwell::addTest(suite, testWrapAround, "testWrapAround");
    Orwell::addTest(suite, testHoledRelease, "holedRelease");
    Orwell::addTest(suite, testHoledWrapAroundRelease, "holedWrapAroundRelease");
  }
}
