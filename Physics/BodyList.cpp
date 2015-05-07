#include "Physics/BodyList.h"

namespace Physics {
  BodyHandle BodyList::create() {
    positions[count] = Fixie::Vector3::zero();
    orientations[count] = Fixie::Quaternion::identity();
    velocities[count] = Fixie::Vector3::zero();
    spins[count] = Fixie::Vector3::zero();
    return count++;
  }

  uint16_t BodyList::getIndex(BodyHandle handle) const {
    return handle;
  }

  ConstBody BodyList::get(BodyHandle handle) const {
    uint16_t index = getIndex(handle);
    ConstBody body;
    body.position = &positions[index];
    body.orientation = &orientations[index];
    body.velocity = &velocities[index];
    body.spin = &spins[index];
    return body;
  }

  Body BodyList::get(BodyHandle handle) {
    uint16_t index = getIndex(handle);
    Body body;
    body.position = &positions[index];
    body.orientation = &orientations[index];
    body.velocity = &velocities[index];
    body.spin = &spins[index];
    return body;
  }

  uint16_t BodyList::getCount() const {
    return count;
  }
}
