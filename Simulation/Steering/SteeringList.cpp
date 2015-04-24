#include "Misc/IntegerPool.h"
#include "Simulation/Steering/SteeringList.h"

namespace Simulation {
  namespace SteeringList {
    using namespace Physics;

    IntegerPool handlePool;
    Fixie::Vector3 targets[Config::steeringMax];
    ForceDriverHandle forceDriverHandles[Config::steeringMax];
    uint16_t indices[Config::steeringMax];
    uint16_t handles[Config::steeringMax];
    uint16_t count = 0;

    SteeringHandle create(ForceDriverHandle forceDriverHandle) {
      assert(Config::steeringMax != count);
      forceDriverHandles[count] = forceDriverHandle;
      SteeringHandle steeringHandle = handlePool.obtain();
      indices[steeringHandle] = count;
      handles[count] = steeringHandle;
      count++;
      return steeringHandle;
    }

    void destroy(SteeringHandle handle) {
      uint16_t removingIndex = indices[handle];

      uint16_t lastIndex = count-1;
      SteeringHandle lastHandle = handles[lastIndex];

      forceDriverHandles[removingIndex] = forceDriverHandles[lastIndex];
      targets[removingIndex] = targets[lastIndex];

      handles[removingIndex] = lastHandle;
      indices[lastHandle] = removingIndex;

      handlePool.release(handle);
      count--;
    }

    Steering get(SteeringHandle handle) {
      Steering steering;
      uint16_t index = indices[handle];
      steering.target = &targets[index];
      steering.forceDriverHandle = forceDriverHandles[index];
      return steering;
    }
  }
}
