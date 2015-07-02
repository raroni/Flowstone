#include <assert.h>
#include "Client/DirectionEventList.h"

namespace Client {
  namespace DirectionEventList {
    const uint16_t max = 128;
    DirectionEvent events[max];
    uint16_t count = 0;

    void add(const DirectionEvent *event) {
      assert(count != max);
      events[count++] = *event;
    }

    const DirectionEvent* get(uint16_t index) {
      return &events[index];
    }

    uint16_t getCount() {
      return count;
    }

    void clear() {
      count = 0;
    }
  }
}
