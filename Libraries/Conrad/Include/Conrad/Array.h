#ifndef CONRAD_ARRAY_H
#define CONRAD_ARRAY_H

#include <assert.h>

template<typename T, size_t SIZE>
class Array {
public:
  const T& operator[](size_t index) const {
    assert(index < SIZE);
    return data[index];
  }
  T& operator[](size_t index) {
    assert(index < SIZE);
    return data[index];
  }
private:
  T data[SIZE];
};

#endif
