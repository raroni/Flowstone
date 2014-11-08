#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Quaternion.h"
#include "Quanta/Geometry/TransformationFactory3D.h"

class FrameInterpolator {
  Quanta::Vector3 oldPositions[128];
  Quanta::Vector3 newPositions[128];
  Quanta::Quaternion oldOrientations[128];
  Quanta::Quaternion newOrientations[128];
  Quanta::Matrix4 transforms[128];
  uint8_t bodyIndices[128];
  uint8_t bodyCount = 0;
public:
  uint8_t createInterpolation(Physics::DynamicBodyIndex body) {
    bodyIndices[bodyCount] = body;
    return bodyCount++;
  }
  void interpolate(double progress) {
    for(uint8_t i=0; bodyCount>i; i++) {
      Quanta::Vector3 position = oldPositions[i] + (newPositions[i]-oldPositions[i])*progress;
      Quanta::Matrix4 translation = Quanta::TransformationFactory3D::translation(position);
      Quanta::Quaternion orientation = Quanta::Quaternion::slerp(oldOrientations[i], newOrientations[i], progress);
      transforms[i] = translation * static_cast<Quanta::Matrix4>(orientation);
    }
  }
  void reload(const Quanta::Vector3 *newPositions, const Quanta::Quaternion *newOrientations) {
    for(uint8_t i=0; bodyCount>i; i++) {
      oldPositions[i] = this->newPositions[i];
      oldOrientations[i] = this->newOrientations[i];
      Physics::DynamicBodyIndex bodyIndex = bodyIndices[i];
      this->newPositions[i] = newPositions[bodyIndex];
      this->newOrientations[i] = newOrientations[bodyIndex];
    }
  }
  const Quanta::Matrix4* getTransforms() const {
    return transforms;
  }
};
