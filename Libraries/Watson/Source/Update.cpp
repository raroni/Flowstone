#include <assert.h>
#include "Misc/Error.h"
#include "Watson/NodeResult.h"
#include "Watson/TypeList.h"
#include "Watson/TraversalFlow.h"
#include "Watson/ResetFlow.h"
#include "Watson/Board.h"
#include "Watson/Server.h"
#include "Watson/BoardCollection.h"
#include "Watson/ActionStreamCollection.h"
#include "Watson/StateCollection.h"
#include "Watson/Node.h"
#include "Watson/Update.h"

namespace Watson {
  namespace Update {
    NodeStack stack;
    Stream requestStream;
    ResponseBuffer responseBuffer;
    TraversalFlow traversalFlow(&requestStream);
    ResetFlow resetFlow(&stack);
    TypeIndex typeIndex;
    uint16_t instanceIndex;

    void configureTraversalFlow(NodeIndex nodeIndex) {
      traversalFlow.structure = TypeList::getStructureNode(typeIndex, nodeIndex);
      traversalFlow.state = StateCollection::getNode(typeIndex, instanceIndex, nodeIndex);
    }

    void runCommand(TraversalCommand *command) {
      switch(command->type) {
        case TraversalCommandType::Entry: {
          NodeIndex nodeIndex = command->options.targetNodeIndex;
          stack.push(nodeIndex);
          configureTraversalFlow(nodeIndex);
          Node::enter(&traversalFlow);
          break;
        }
        case TraversalCommandType::Reaction: {
          stack.pop();
          if(stack.isEmpty()) {
            return;
          }
          traversalFlow.lastResult = command->options.result;
          NodeIndex nodeIndex = stack.top();
          configureTraversalFlow(nodeIndex);
          Node::react(&traversalFlow);
          break;
        }
        case TraversalCommandType::Callback: {
          NodeIndex nodeIndex = stack.top();
          configureTraversalFlow(nodeIndex);
          Node::callback(&traversalFlow, command->options.callbackIndex);
          break;
        }
        default: {
          fatalError("Unknown traversal command type.");
        }
      }
    }

    void run(TypeIndex newTypeIndex, uint16_t newInstanceIndex) {
      typeIndex = newTypeIndex;
      instanceIndex = newInstanceIndex;
      traversalFlow.board = BoardCollection::get(typeIndex, instanceIndex);
      traversalFlow.actionStream = ActionStreamCollection::get(typeIndex, instanceIndex);
      traversalFlow.requestEntry(0);
      while(1) {
        TraversalCommand command = traversalFlow.getCommand();
        traversalFlow.resetCommand();
        runCommand(&command);
        if(traversalFlow.getCommand().type == TraversalCommandType::Undefined) {
          break;
        }
        for(uint8_t i=0; i<requestStream.getCount(); ++i) {
          const uint8_t *request = static_cast<const uint8_t*>(requestStream.get(i));
          Server::request(*request, request+1, &responseBuffer);
          traversalFlow.board->set(*request, responseBuffer.storage, responseBuffer.length);
        }
        requestStream.clear();
      }

      assert(stack.isEmpty());

      NodeIndex resetNodeIndex = traversalFlow.getResetNodeIndex();
      if(resetNodeIndex != 0) {
        stack.push(resetNodeIndex);
        while(stack.isEmpty()) {
          NodeIndex nodeIndex = stack.pop();
          resetFlow.structure = TypeList::getStructureNode(typeIndex, nodeIndex);
          resetFlow.state = StateCollection::getNode(typeIndex, instanceIndex, nodeIndex);
          Node::reset(&resetFlow);
        }
      }
    }
  }
}
