#include "Misc/IntegerPool.h"
#include "Physics/ForceDriverHandle.h"
#include "Physics/ForceDriver.h"
#include "Physics/Body.h"
#include "Simulation/Config.h"
#include "Simulation/PhysicsHack.h"
#include "Simulation/Drag/DragSystem.h"

namespace Simulation {
  namespace DragSystem {
    using namespace Physics;

    IntegerPool handlePool;
    ForceDriverHandle forceDriverHandles[Config::dragMax];
    uint16_t indices[Config::dragMax];
    uint16_t handles[Config::dragMax];
    uint16_t count = 0;

    DragHandle create(ForceDriverHandle forceDriverHandle) {
      assert(Config::dragMax != count);
      forceDriverHandles[count] = forceDriverHandle;
      DragHandle dragHandle = handlePool.obtain();
      indices[dragHandle] = count;
      handles[count] = dragHandle;
      count++;
      return dragHandle;
    }

    void destroy(DragHandle handle) {
      assert(count != 0);
      uint16_t removingIndex = indices[handle];

      uint16_t lastIndex = count-1;
      DragHandle lastHandle = handles[lastIndex];

      forceDriverHandles[removingIndex] = forceDriverHandles[lastIndex];

      handles[removingIndex] = lastHandle;
      indices[lastHandle] = removingIndex;

      handlePool.release(handle);
      count--;
    }

    void update() {
      for(uint16_t i=0; i<count; ++i) {
        ForceDriverHandle forceDriverHandle = forceDriverHandles[i];
        Physics::ForceDriver driver = physicsEngine.getForceDriver(forceDriverHandle);
        Physics::Body body = physicsEngine.getBody(driver.bodyHandle);
        (*driver.force) += (*body.velocity) * Fixie::Num(-2);
        (*driver.torque) += (*body.spin) * Fixie::Num(-4);
      }
    }
  }
}
