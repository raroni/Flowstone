#ifndef WATSON_SERVER_FUNCTION_H
#define WATSON_SERVER_FUNCTION_H

#include "Watson/ResponseBuffer.h"
#include "Watson/Board.h"

namespace Watson {
  typedef void (*ServerFunction)(const void *requestData, const Board *board, ResponseBuffer *responseBuffer);
}

#endif
