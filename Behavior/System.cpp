#include <assert.h>
#include "Actions3/System.h"
#include "Misc/HandleList.h"
#include "Watson/InstanceHandle.h"
#include "Watson/System.h"
#include "Watson/Stream.h"
#include "Watson/TypeIndex.h"
#include "Behavior/NodeTypes.h"
#include "Behavior/BoardKey.h"
#include "Behavior/TreeTypes.h"
#include "Behavior/Server.h"
#include "Behavior/System.h"

namespace Behavior {
  namespace System {
    const static uint16_t max = 256;
    uint16_t indices[max];
    Handle handles[max];
    HandleList handleList(max, indices, handles);
    Watson::InstanceHandle instanceHandles[max];
    BehaviorType behaviorTypes[max];
    Actions3::InstanceHandle actionsHandles[max];

    void setup() {
      Watson::System::initialize();
      Server::setup();
      NodeTypes::setup();
      TreeTypes::setup();
    }

    Handle create(Actions3::InstanceHandle actionsHandle, BehaviorType behaviorType) {
      assert(handleList.getCount() != max);
      uint16_t index;
      Handle handle;
      handleList.create(&index, &handle);
      instanceHandles[index] = Watson::System::createInstance(TreeTypes::workerIndex);
      actionsHandles[index] = actionsHandle;
      behaviorTypes[index] = behaviorType;

      assert(behaviorType == BehaviorType::Worker);
      // Todo:
      // We should support more types.
      // We should make some kind of "[type] list"
      // so we can add special abilities depending
      // on types. Must also fix destroy() accordingly.

      return handle;
    }

    void requestActions() {
      uint8_t actionHandleBoardKey = static_cast<uint8_t>(BoardKey::ActionsHandle);
      for(Watson::TypeIndex t=0; t<Watson::System::getTypeCount(); ++t) {
        for(uint16_t i=0; i<Watson::System::getInstanceCount(t); ++i) {
          Watson::Stream *actionStream = Watson::System::getActionStream(t, i);
          Watson::Board *board = Watson::System::getBoardByIndices(t, i);
          Actions3::InstanceHandle handle = *reinterpret_cast<const Actions3::InstanceHandle*>(board->get(actionHandleBoardKey));
          for(uint8_t a=0; a<actionStream->getCount(); ++a) {
            void *actionData = actionStream->get(a);
            Actions3::Request request;
            request.type = *reinterpret_cast<Actions3::ActionType*>(actionData);
            Actions3::System::request(handle, &request);
          }
        }
      }
    }

    void populateActionsHandles() {
      uint8_t keyInt = static_cast<uint8_t>(BoardKey::ActionsHandle);
      for(uint16_t i=0; i<handleList.getCount(); ++i) {
        Watson::InstanceHandle instanceHandle = instanceHandles[i];
        Watson::Board *board = Watson::System::getBoardByHandle(instanceHandle);
        board->set(keyInt, &actionsHandles[i], sizeof(actionsHandles[i]));
      }
    }

    void update() {
      populateActionsHandles();
      Watson::System::update();
      requestActions();
      Watson::System::clearActionStreams();
    }
  }
}
