#include "Actions/NodeStructureHeader.h"
#include "Actions/Node.h"
#include "Actions/ActionStateCollection.h"
#include "Actions/ActionTypeList.h"
#include "Actions/NodeFlow.h"

namespace Actions {
  NodeFlow::NodeFlow() { }
  NodeFlow::NodeFlow(ActionTypeIndex actionTypeIndex, ActionStateIndex actionStateIndex) {
    configure(actionTypeIndex, actionStateIndex);
  }

  void NodeFlow::configure(ActionTypeIndex actionTypeIndex, ActionStateIndex actionStateIndex) {
    this->actionTypeIndex = actionTypeIndex;
    this->actionStateIndex = actionStateIndex;
  }

  void NodeFlow::prepare(NodeIndex nodeIndex) {
    structure = static_cast<const char*>(ActionTypeList::getNodeStructure(actionTypeIndex, nodeIndex));
    state = ActionStateCollection::getNodeState(actionTypeIndex, actionStateIndex, nodeIndex);
  }

  NodeTypeIndex NodeFlow::getNodeType() const {
    return *reinterpret_cast<const NodeTypeIndex*>(structure);
  }

  void NodeFlow::start(NodeIndex nodeIndex) {
    prepare(nodeIndex);
    Node::start(this);
  }

  bool NodeFlow::isCompleted(NodeIndex nodeIndex) {
    prepare(nodeIndex);
    return Node::isCompleted(this);
  }

  const void* NodeFlow::getConfig() const {
    return static_cast<const char*>(structure)+sizeof(NodeStructureHeader);
  }

  void* NodeFlow::getState() {
    return state;
  }
}
