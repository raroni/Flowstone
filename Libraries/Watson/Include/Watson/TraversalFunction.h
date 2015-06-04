#ifndef WATSON_TRAVERSAL_FUNCTION_H
#define WATSON_TRAVERSAL_FUNCTION_H

#include "Watson/TraversalFlow.h"

namespace Watson {
  typedef void (*TraversalFunction)(TraversalFlow *flow);
}

#endif
