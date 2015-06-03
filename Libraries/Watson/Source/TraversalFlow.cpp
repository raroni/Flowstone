#include <assert.h>
#include "Watson/TraversalFlow.h"

namespace Watson {
  void TraversalFlow::requestReaction(NodeResult result) {
    assert(command.type == TraversalCommandType::Undefined);
    command.type = TraversalCommandType::Reaction;
    command.options.result = result;
  }

  void TraversalFlow::requestEntry(NodeIndex node) {
    assert(command.type == TraversalCommandType::Undefined);
    command.type = TraversalCommandType::Entry;
    command.options.targetNodeIndex = node;
  }

  void TraversalFlow::requestReset(NodeIndex node) {
    assert(resetNodeIndex == 0);
    assert(node != 0);
    resetNodeIndex = node;
  }

  void TraversalFlow::requestCallback(uint8_t callbackIndex) {
    assert(command.type == TraversalCommandType::Undefined);
    command.type = TraversalCommandType::Callback;
    command.options.callbackIndex = callbackIndex;
  }

  void TraversalFlow::resetCommand() {
    command.type = TraversalCommandType::Undefined;
  }

  TraversalCommand TraversalFlow::getCommand() const {
    return command;
  }

  NodeIndex TraversalFlow::getResetNodeIndex() const {
    return resetNodeIndex;
  }
}
