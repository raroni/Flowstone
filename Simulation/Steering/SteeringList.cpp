#include "Misc/HandleList.h"
#include "Simulation/Steering/SteeringList.h"

namespace Simulation {
  namespace SteeringList {
    using namespace Physics;

    static const uint16_t max = Config::steeringMax;
    Fixie::Vector3 targets[max];
    DynamicDriverHandle dynamicDriverHandles[max];
    uint16_t indices[max];
    uint16_t handles[max];
    HandleList handleList(max, indices, handles);

    SteeringHandle create(DynamicDriverHandle dynamicDriverHandle) {
      uint16_t index;
      SteeringHandle steeringHandle;
      handleList.create(&index, &steeringHandle);
      dynamicDriverHandles[index] = dynamicDriverHandle;
      return steeringHandle;
    }

    void destroy(SteeringHandle handle) {
      uint16_t sourceIndex, destinationIndex;
      handleList.destroy(handle, &sourceIndex, &destinationIndex);
      dynamicDriverHandles[destinationIndex] = dynamicDriverHandles[sourceIndex];
      targets[destinationIndex] = targets[sourceIndex];
    }

    uint16_t getCount() {
      return handleList.getCount();
    }

    Steering get(SteeringHandle handle) {
      uint16_t index = handleList.getIndex(handle);
      Steering steering;
      steering.target = &targets[index];
      steering.dynamicDriverHandle = dynamicDriverHandles[index];
      return steering;
    }
  }
}
