#include "Actions/Node.h"
#include "Actions/NodeFlow.h"

namespace Actions {
  NodeFlow::NodeFlow() { }

  NodeFlow::NodeFlow(ActionTypeIndex actionTypeIndex, ActionStateIndex actionStateIndex, Database::EntityHandle entityHandle) {
    configure(actionTypeIndex, actionStateIndex, entityHandle);
  }

  void NodeFlow::configure(ActionTypeIndex actionTypeIndex, ActionStateIndex actionStateIndex, Database::EntityHandle entityHandle) {
    this->actionTypeIndex = actionTypeIndex;
    this->actionStateIndex = actionStateIndex;
    this->entityHandle = entityHandle;
  }

  void NodeFlow::start(NodeIndex nodeIndex) {
    NodeCall call(this, nodeIndex);
    Node::start(&call);
  }

  bool NodeFlow::isCompleted(NodeIndex nodeIndex) {
    NodeCall call(this, nodeIndex);
    return Node::isCompleted(&call);
  }

  ActionStateIndex NodeFlow::getActionStateIndex() const {
    return actionStateIndex;
  }

  ActionTypeIndex NodeFlow::getActionTypeIndex() const {
    return actionTypeIndex;
  }

  Database::EntityHandle NodeFlow::getEntityHandle() const {
    return entityHandle;
  }
}
