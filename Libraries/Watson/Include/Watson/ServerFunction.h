#ifndef WATSON_SERVER_FUNCTION_H
#define WATSON_SERVER_FUNCTION_H

#include "Watson/Request.h"
#include "Watson/Board.h"

namespace Watson {
  typedef void (*ServerFunction)(const Request *request, Board *board);
}

#endif
