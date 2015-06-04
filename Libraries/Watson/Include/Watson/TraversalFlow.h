#ifndef WATSON_TRAVERSAL_FLOW_H
#define WATSON_TRAVERSAL_FLOW_H

#include "Watson/NodeResult.h"
#include "Watson/TraversalCommand.h"
#include "Watson/NodeIndex.h"
#include "Watson/Board.h"
#include "Watson/Stream.h"

namespace Watson {
  class TraversalFlow {
  public:
    TraversalFlow(Stream *requestStream);
    void requestReaction(NodeResult result);
    void requestEntry(NodeIndex node);
    void requestReset(NodeIndex node);
    void requestCallback(uint8_t callbackIndex);
    void requestBoardData(const void *request, uint8_t length);
    void resetCommand();
    TraversalCommand getCommand() const;
    NodeResult lastResult;
    Board* board = nullptr;
    Stream* actionStream = nullptr;
    const void *structure = nullptr;
    void *state = nullptr;
    NodeIndex getResetNodeIndex() const;
  private:
    Stream* requestStream = nullptr;
    TraversalCommand command;
    NodeIndex resetNodeIndex;
  };
}

#endif
