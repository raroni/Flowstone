#include <assert.h>
#include "ServerControlQueue.h"

ServerControlCommand ServerControlQueue::getNext() const {
  return list[tail];
}

void ServerControlQueue::next() {
  assert(count != 0);
  count--;
  tail = (tail+1) % 8;
}

void ServerControlQueue::push(ServerControlCommand command) {
  assert(count != max);
  list[head] = command;
  count++;
  head = (head+1) % max;
}

uint16_t ServerControlQueue::getCount() const {
  return count;
}
