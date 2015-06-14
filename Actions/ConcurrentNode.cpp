#include "Actions/NodeIndex.h"
#include "Actions/ConcurrentNode.h"

namespace Actions {
  namespace ConcurrentNode {
    uint8_t calcConfigLength(const void *args) {
      return ParentNode::calcConfigLength(args);
    }

    uint8_t calcStateLength(const void *args) {
      return 0;
    }

    void configure(const void *args, void *config) {
      ParentNode::configure(args, config);
    }

    bool isCompleted(NodeFlow *flow) {
      return false;
    }

    void start(NodeFlow *flow) {
      const void *config = flow->getConfig();
      uint8_t childCount = ParentNode::getChildCount(config);
      const NodeIndex *children = ParentNode::getChildren(config);
      for(uint8_t i=0; i<childCount; ++i) {
        flow->start(children[i]);
      }
    }
  }
}
