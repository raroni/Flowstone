#include <assert.h>
#include "HandleList.h"

HandleList::HandleList() { }

HandleList::HandleList(uint16_t max, uint16_t *indices, uint16_t *handles) {
  configure(max, indices, handles);
}

void HandleList::configure(uint16_t max, uint16_t *indices, uint16_t *handles) {
  this->max = max;
  this->indices = indices;
  this->handles = handles;
}

void HandleList::create(uint16_t *index, uint16_t *handle) {
  assert(max != count);
  *index = count;
  *handle = handlePool.obtain();
  indices[*handle] = count;
  handles[*index] = *handle;
  count++;
}

void HandleList::destroy(uint16_t handle, uint16_t *sourceIndex, uint16_t *destinationIndex) {
  *destinationIndex = indices[handle];
  *sourceIndex = count-1;
  uint16_t sourceHandle = handles[*sourceIndex];

  handles[*destinationIndex] = sourceHandle;
  indices[sourceHandle] = *destinationIndex;

  handlePool.release(handle);
  count--;
}

uint16_t HandleList::getIndex(uint16_t handle) const {
  return indices[handle];
}

uint16_t HandleList::getCount() const {
  return count;
}
