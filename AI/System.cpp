#include <assert.h>
#include "Misc/HandleList.h"
#include "Watson/InstanceHandle.h"
#include "Watson/System.h"
#include "AI/NodeTypes.h"
#include "AI/TreeTypes.h"
#include "AI/Server.h"
#include "AI/System.h"

namespace AI {
  namespace System {
    const static uint16_t max = 256;
    uint16_t indices[max];
    Handle handles[max];
    BehaviorType behaviorTypes[max];
    Watson::InstanceHandle instanceHandles[max];
    HandleList handleList(max, indices, handles);

    void setup() {
      Watson::System::initialize();
      Server::setup();
      NodeTypes::setup();
      TreeTypes::setup();
    }

    Handle create(BehaviorType behaviorType) {
      assert(handleList.getCount() != max);
      uint16_t index;
      Handle handle;
      handleList.create(&index, &handle);
      instanceHandles[index] = Watson::System::createInstance(TreeTypes::monsterIndex);
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
      Watson::System::update();
    }
  }
}
