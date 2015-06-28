#include "Actions/NodeStructureHeader.h"
#include "Actions/ActionStateCollection.h"
#include "Actions/ActionTypeList.h"
#include "Actions/NodeCall.h"

namespace Actions {
  NodeCall::NodeCall(NodeFlow *flow, NodeIndex nodeIndex) : flow(flow) {
    ActionTypeIndex typeIndex = flow->getActionTypeIndex();
    ActionStateIndex stateIndex = flow->getActionStateIndex();
    structure = ActionTypeList::getNodeStructure(typeIndex, nodeIndex);
    state = ActionStateCollection::getNodeState(typeIndex, stateIndex, nodeIndex);
  }

  NodeTypeIndex NodeCall::getNodeType() const {
    return *reinterpret_cast<const NodeTypeIndex*>(structure);
  }

  const void* NodeCall::getConfig() const {
    return static_cast<const char*>(structure)+sizeof(NodeStructureHeader);
  }

  NodeFlow* NodeCall::getFlow() {
    return flow;
  }

  void* NodeCall::getState() {
    return state;
  }
}
