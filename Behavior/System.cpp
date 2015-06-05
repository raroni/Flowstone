#include <assert.h>
#include "Misc/HandleList.h"
#include "Watson/InstanceHandle.h"
#include "Watson/System.h"
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
    Actions::Handle actionsHandles[max];

    void setup() {
      Watson::System::initialize();
      Server::setup();
      NodeTypes::setup();
      TreeTypes::setup();
    }

    Handle create(Actions::Handle actionsHandle, BehaviorType behaviorType) {
      assert(handleList.getCount() != max);
      uint16_t index;
      Handle handle;
      handleList.create(&index, &handle);
      instanceHandles[index] = Watson::System::createInstance(TreeTypes::monsterIndex);
      actionsHandles[index] = actionsHandle;
      behaviorTypes[index] = behaviorType;

      assert(behaviorType == BehaviorType::Monster);
      // Todo:
      // We should support more types.
      // We should make some kind of "[type] list"
      // so we can add special abilities depending
      // on types. Must also fix destroy() accordingly.

      return handle;
    }

    void update() {
      for(uint16_t i=0; i<handleList.getCount(); ++i) {
        Watson::InstanceHandle instanceHandle = instanceHandles[i];
        Watson::Board *board = Watson::System::getBoard(instanceHandle);
        uint8_t keyInt = static_cast<uint8_t>(BoardKey::ActionsHandle);
        board->set(keyInt, &actionsHandles[i], sizeof(actionsHandles[i]));
      }

      Watson::System::update();

      // todo: treat action streams

      Watson::System::clearActionStreams();
    }
  }
}
