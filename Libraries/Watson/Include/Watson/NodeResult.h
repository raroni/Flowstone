#ifndef WATSON_NODE_RESULT_H
#define WATSON_NODE_RESULT_H

namespace Watson {
  enum class NodeResult : char {
    Running,
    Succeeded,
    Failed,
    Undetermined
  };
}

#endif
