#include "Quanta/Geometry/TransformFactory3D.h"
#include "Client/MathConversion.h"
#include "Client/Interpolater.h"

namespace Client {
  using namespace MathConversion;

  Interpolater interpolater;

  void Interpolater::prepare(const Physics::BodyList &bodies) {
    for(uint8_t i=0; count>i; i++) {
      Physics::BodyHandle handle = bodyHandles[i];
      Physics::ConstBody body = bodies.get(handle);

      convertVector(oldPositions[i], *(body.position));
      convertVector(newPositions[i], *(body.position));
      convertQuaternion(newOrientations[i], *(body.orientation));
      convertQuaternion(oldOrientations[i], *(body.orientation));
    }
    interpolate(0);
  }

  void Interpolater::interpolate(double progress) {
    for(uint8_t i=0; count>i; i++) {
      Quanta::Vector3 position = oldPositions[i] + (newPositions[i]-oldPositions[i])*progress;
      Quanta::Matrix4 translation = Quanta::TransformFactory3D::translation(position);
      Quanta::Quaternion orientation = Quanta::Quaternion::slerp(oldOrientations[i], newOrientations[i], progress);
      transforms[i] = translation * static_cast<Quanta::Matrix4>(orientation);
    }
  }

  InterpolationHandle Interpolater::createInterpolation(Physics::BodyHandle body) {
    assert(max != count);
    bodyHandles[count] = body;
    return count++;
  }

  void Interpolater::reload(const Physics::BodyList &bodies) {
    for(uint8_t i=0; count>i; i++) {
      Physics::BodyHandle handle = bodyHandles[i];
      Physics::ConstBody body = bodies.get(handle);

      oldPositions[i] = this->newPositions[i];
      oldOrientations[i] = this->newOrientations[i];
      convertVector(this->newPositions[i], *(body.position));
      convertQuaternion(this->newOrientations[i], *(body.orientation));
    }
  }

  const Quanta::Matrix4* Interpolater::getTransforms() const {
    return transforms;
  }
}
