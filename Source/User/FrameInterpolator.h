#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Quaternion.h"

class FrameInterpolator {
  Quanta::Vector3 oldPositions[128];
  Quanta::Vector3 newPositions[128];
  Quanta::Quaternion oldOrientations[128];
  Quanta::Quaternion newOrientations[128];
  Quanta::Matrix4 transforms[128];
public:
  uint8_t createTransform(uint8_t physicsTransformID) {
    return 0;
  }
  void interpolate(double rest) {

  }
  void reload(const Quanta::Vector3 *newPositions, const Quanta::Quaternion *newOrientations) {

  }
  const Quanta::Matrix4* getTransforms() const {
    return transforms;
  }
};
