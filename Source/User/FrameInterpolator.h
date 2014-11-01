#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Quaternion.h"
#include "Quanta/Geometry/TransformationFactory3D.h"

class FrameInterpolator {
  Quanta::Vector3 oldPositions[128];
  Quanta::Vector3 newPositions[128];
  Quanta::Quaternion oldOrientations[128];
  Quanta::Quaternion newOrientations[128];
  Quanta::Matrix4 transforms[128];
  uint8_t physicsTransformIDs[128];
  uint8_t transformsCount = 0;
public:
  uint8_t createTransform(uint8_t physicsTransformID) {
    physicsTransformIDs[transformsCount] = physicsTransformID;
    return transformsCount++;
  }
  void interpolate(double progress) {
    for(uint8_t i=0; transformsCount>i; i++) {
      Quanta::Vector3 position = oldPositions[i] + (oldPositions[i]-newPositions[i])*progress;
      transforms[i] = Quanta::TransformationFactory3D::translation(position);
    }
  }
  void reload(const Quanta::Vector3 *newPositions, const Quanta::Quaternion *newOrientations) {
    for(uint8_t i=0; transformsCount>i; i++) {
      oldPositions[i] = this->newPositions[i];
      uint8_t physicsTransformID = physicsTransformIDs[i];
      this->newPositions[i] = newPositions[physicsTransformID];
    }
  }
  const Quanta::Matrix4* getTransforms() const {
    return transforms;
  }
};
