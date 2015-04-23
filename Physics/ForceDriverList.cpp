#include "Physics/ForceDriverList.h"

namespace Physics {
  uint16_t ForceDriverList::getCount() const {
    return count;
  }

  ForceDriver ForceDriverList::get(ForceDriverHandle handle) {
    ForceDriver driver;
    uint16_t index = handle;
    driver.force = &forces[index];
    driver.bodyHandle = bodyHandles[index];
    return driver;
  }

  ForceDriverHandle ForceDriverList::create(BodyHandle bodyHandle) {
    bodyHandles[count] = bodyHandle;
    forces[count] = Fixie::Vector3::zero();
    return count++;
  }
}
