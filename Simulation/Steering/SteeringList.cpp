#include "Misc/HandleList.h"
#include "Simulation/Steering/SteeringList.h"

namespace Simulation {
  namespace SteeringList {
    using namespace Physics;

    static const uint16_t max = Config::steeringMax;
    Fixie::Vector3 targets[max];
    DynamicDriverHandle dynamicDriverHandles[max];
    Database::EntityHandle entityHandles[max];
    uint16_t indices[max];
    uint16_t handles[max];
    HandleList handleList(max, indices, handles);

    SteeringHandle create(Database::EntityHandle entity, Physics::DynamicDriverHandle physicsDriver) {
      uint16_t index;
      SteeringHandle steeringHandle;
      handleList.create(&index, &steeringHandle);
      entityHandles[index] = entity;
      dynamicDriverHandles[index] = physicsDriver;
      return steeringHandle;
    }

    void destroy(SteeringHandle handle) {
      uint16_t sourceIndex, destinationIndex;
      handleList.destroy(handle, &sourceIndex, &destinationIndex);
      entityHandles[destinationIndex] = entityHandles[sourceIndex];
      dynamicDriverHandles[destinationIndex] = dynamicDriverHandles[sourceIndex];
      targets[destinationIndex] = targets[sourceIndex];
    }

    uint16_t getCount() {
      return handleList.getCount();
    }

    Steering get(SteeringHandle handle) {
      uint16_t index = handleList.getIndex(handle);
      Steering steering = {
        .target = &targets[index],
        .dynamicDriverHandle = dynamicDriverHandles[index],
        .entityHandle = entityHandles[index]
      };
      return steering;
    }
  }
}
