#ifndef CONRAD_LIST_H
#define CONRAD_LIST_H

#include <stddef.h>
#include <assert.h>

template<typename T, size_t MAX_COUNT>
class List {
public:
  T objects[MAX_COUNT];
  uint8_t count = 0;
  void add(T object) {
    objects[count++] = object;
  }
  bool full() {
    return count == MAX_COUNT;
  }
  uint8_t getCount() {
    return count;
  }
  const T& operator[](const uint8_t index) {
    assert(index < count);
    return objects[index];
  }
  void clear() {
    count = 0;
  }
};

#endif
