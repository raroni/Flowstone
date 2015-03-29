#ifndef SERVER_CONTROL_QUEUE_H
#define SERVER_CONTROL_QUEUE_H

#include <stdint.h>
#include "ServerControlCommand.h"

class ServerControlQueue {
public:
  ServerControlCommand getNext() const;
  void next();
  void push(ServerControlCommand command);
  uint16_t getCount() const;
private:
  const static uint8_t max = 8;
  uint8_t head = 0;
  uint8_t tail = 0;
  uint8_t count = 0;
  ServerControlCommand list[max];
};

#endif
