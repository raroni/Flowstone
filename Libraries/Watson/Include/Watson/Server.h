#ifndef WATSON_SERVER_H
#define WATSON_SERVER_H

#include <stdint.h>
#include "Watson/Board.h"
#include "Watson/ServerFunction.h"

namespace Watson {
  namespace Server {
    void configure(uint8_t boardKey, ServerFunction function);
    void request(uint8_t boardKey, const void *requestData, const Board *board, ResponseBuffer *responseBuffer);
  }
}

#endif
