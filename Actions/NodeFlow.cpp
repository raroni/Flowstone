#include "Actions/NodeStructureHeader.h"
#include "Actions/Node.h"
#include "Actions/ActionStateCollection.h"
#include "Actions/ActionTypeList.h"
#include "Actions/NodeFlow.h"

namespace Actions {
  NodeFlow::NodeFlow(ActionTypeIndex actionTypeIndex, ActionStateIndex actionStateIndex) :
  actionTypeIndex(actionTypeIndex),
  actionStateIndex(actionStateIndex) { }

  void NodeFlow::start(NodeIndex nodeIndex) {
    const char *structure = static_cast<const char*>(ActionTypeList::getNodeStructure(actionTypeIndex, nodeIndex));
    NodeTypeIndex nodeTypeIndex = *reinterpret_cast<const NodeTypeIndex*>(structure);
    config = structure+sizeof(NodeStructureHeader);
    state = ActionStateCollection::getNodeState(actionTypeIndex, actionStateIndex, nodeIndex);
    Node::start(nodeTypeIndex, this);
  }

  const void* NodeFlow::getConfig() const {
    return config;
  }

  void* NodeFlow::getState() {
    return state;
  }
}
