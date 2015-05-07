#include "Physics/DynamicDriverList.h"

namespace Physics {
  uint16_t DynamicDriverList::getCount() const {
    return count;
  }

  DynamicDriver DynamicDriverList::get(DynamicDriverHandle handle) {
    DynamicDriver driver;
    uint16_t index = handle;
    driver.force = &forces[index];
    driver.torque = &torques[index];
    driver.bodyHandle = bodyHandles[index];
    return driver;
  }

  DynamicDriverHandle DynamicDriverList::create(BodyHandle bodyHandle) {
    bodyHandles[count] = bodyHandle;
    forces[count] = Fixie::Vector3::zero();
    torques[count] = Fixie::Vector3::zero();
    return count++;
  }
}
