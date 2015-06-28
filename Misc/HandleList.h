#ifndef HANDLE_LIST_H
#define HANDLE_LIST_H

#include "Misc/IntegerPool.h"

class HandleList {
  public:
    HandleList(uint16_t max, uint16_t *indices, uint16_t *handles);
    HandleList();
    void configure(uint16_t max, uint16_t *indices, uint16_t *handles);
    void create(uint16_t *index, uint16_t *handle);
    void destroy(uint16_t handle, uint16_t *sourceIndex, uint16_t *destinationIndex);
    uint16_t getIndex(uint16_t handle) const;
    uint16_t getCount() const;
  private:
    IntegerPool handlePool;
    uint16_t count = 0;
    uint16_t max;
    uint16_t *indices;
    uint16_t *handles;
};

#endif
