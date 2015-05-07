#include "Misc/IntegerPool.h"
#include "Physics/DynamicDriverHandle.h"
#include "Physics/DynamicDriver.h"
#include "Physics/Body.h"
#include "Simulation/Config.h"
#include "Simulation/PhysicsHack.h"
#include "Simulation/Drag/DragSystem.h"

namespace Simulation {
  namespace DragSystem {
    using namespace Physics;

    IntegerPool handlePool;
    DynamicDriverHandle dynamicDriverHandles[Config::dragMax];
    uint16_t indices[Config::dragMax];
    uint16_t handles[Config::dragMax];
    uint16_t count = 0;

    DragHandle create(DynamicDriverHandle dynamicDriverHandle) {
      assert(Config::dragMax != count);
      dynamicDriverHandles[count] = dynamicDriverHandle;
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

      dynamicDriverHandles[removingIndex] = dynamicDriverHandles[lastIndex];

      handles[removingIndex] = lastHandle;
      indices[lastHandle] = removingIndex;

      handlePool.release(handle);
      count--;
    }

    void update() {
      for(uint16_t i=0; i<count; ++i) {
        DynamicDriverHandle dynamicDriverHandle = dynamicDriverHandles[i];
        Physics::DynamicDriver driver = physicsEngine.getDynamicDriver(dynamicDriverHandle);
        Physics::Body body = physicsEngine.getBody(driver.bodyHandle);
        (*driver.force) += (*body.velocity) * Fixie::Num(-2);
        (*driver.torque) += (*body.spin) * Fixie::Num(-4);
      }
    }
  }
}
