#include "Misc/HandleList.h"
#include "Simulation/Steering/SteeringList.h"

namespace Simulation {
  namespace SteeringList {
    using namespace Physics;

    static const uint16_t max = Config::steeringMax;
    Fixie::Vector3 targets[max];
    ForceDriverHandle forceDriverHandles[max];
    uint16_t indices[max];
    uint16_t handles[max];
    HandleList handleList(max, indices, handles);

    SteeringHandle create(ForceDriverHandle forceDriverHandle) {
      uint16_t index;
      SteeringHandle steeringHandle;
      handleList.create(&index, &steeringHandle);
      forceDriverHandles[index] = forceDriverHandle;
      return steeringHandle;
    }

    void destroy(SteeringHandle handle) {
      uint16_t sourceIndex, destinationIndex;
      handleList.destroy(handle, &sourceIndex, &destinationIndex);
      forceDriverHandles[destinationIndex] = forceDriverHandles[sourceIndex];
      targets[destinationIndex] = targets[sourceIndex];
    }

    uint16_t getCount() {
      return handleList.getCount();
    }

    Steering get(SteeringHandle handle) {
      uint16_t index = handleList.getIndex(handle);
      Steering steering;
      steering.target = &targets[index];
      steering.forceDriverHandle = forceDriverHandles[index];
      return steering;
    }
  }
}
