#include "Misc/HandleList.h"
#include "Orwell.h"

namespace HandleListTest {
  using namespace Orwell::Assertions;

  typedef uint16_t TestHandle;

  void testCreation() {
    uint16_t max = 8;
    TestHandle handles[max];
    uint16_t indices[max];
    HandleList list(max, indices, handles);
    uint16_t index, handle, sourceIndex, destinationIndex;

    list.create(&index, &handle);
    assertEqual(0, handle);
    assertEqual(0, index);

    list.create(&index, &handle);
    assertEqual(1, handle);
    assertEqual(1, index);

    list.create(&index, &handle);
    assertEqual(2, handle);
    assertEqual(2, index);

    list.destroy(1, &sourceIndex, &destinationIndex);
    list.create(&index, &handle);
    assertEqual(1, handle);
    assertEqual(2, index);
  }

  void testCount() {
    uint16_t max = 8;
    TestHandle handles[max];
    uint16_t indices[max];
    HandleList list(max, indices, handles);
    uint16_t index, handle, sourceIndex, destinationIndex;

    assertEqual(0, list.getCount());

    list.create(&index, &handle);
    assertEqual(1, list.getCount());

    list.create(&index, &handle);
    assertEqual(2, list.getCount());

    list.destroy(0, &sourceIndex, &destinationIndex);
    assertEqual(1, list.getCount());

    list.create(&index, &handle);
    assertEqual(2, list.getCount());
  }

  void testDestruction() {
    uint16_t max = 8;
    TestHandle handles[max];
    uint16_t indices[max];
    HandleList list(max, indices, handles);
    uint16_t index, handle, sourceIndex, destinationIndex;

    list.create(&index, &handle);
    list.create(&index, &handle);
    list.create(&index, &handle);

    list.destroy(1, &sourceIndex, &destinationIndex);
    assertEqual(2, sourceIndex);
    assertEqual(1, destinationIndex);

    list.create(&index, &handle);
    list.create(&index, &handle);

    list.destroy(2, &sourceIndex, &destinationIndex);
    assertEqual(3, sourceIndex);
    assertEqual(1, destinationIndex);
  }

  void setup() {
    unsigned group = Orwell::createGroup("HandleList");
    Orwell::addTest(group, testCreation, "Creation");
    Orwell::addTest(group, testCount, "Count");
    Orwell::addTest(group, testDestruction, "Destruction");
  }
}
