#include "Quanta/Geometry/TransformFactory3D.h"
#include "Client/MathConversion.h"
#include "Client/Interpolation/Interpolater.h"

namespace Client {
  namespace Interpolation {
    using namespace MathConversion;

    void Interpolater::initialize(const Fixie::Vector3 *positions, const Fixie::Quaternion *orientations) {
      for(uint8_t i=0; bodyCount>i; i++) {
        Physics::DynamicBodyIndex bodyIndex = bodyIndices[i];
        convertVector(oldPositions[i], positions[bodyIndex]);
        convertVector(newPositions[i], positions[bodyIndex]);
        convertQuaternion(newOrientations[i], orientations[bodyIndex]);
        convertQuaternion(oldOrientations[i], orientations[bodyIndex]);
      }
      interpolate(0);
    }

    void Interpolater::interpolate(double progress) {
      for(uint8_t i=0; bodyCount>i; i++) {
        Quanta::Vector3 position = oldPositions[i] + (newPositions[i]-oldPositions[i])*progress;
        Quanta::Matrix4 translation = Quanta::TransformFactory3D::translation(position);
        Quanta::Quaternion orientation = Quanta::Quaternion::slerp(oldOrientations[i], newOrientations[i], progress);
        transforms[i] = translation * static_cast<Quanta::Matrix4>(orientation);
      }
    }

    Index Interpolater::createInterpolation(Physics::DynamicBodyIndex body) {
      bodyIndices[bodyCount] = body;
      return bodyCount++;
    }

    void Interpolater::reload(const Fixie::Vector3 *newPositions, const Fixie::Quaternion *newOrientations) {
      for(uint8_t i=0; bodyCount>i; i++) {
        oldPositions[i] = this->newPositions[i];
        oldOrientations[i] = this->newOrientations[i];
        Physics::DynamicBodyIndex bodyIndex = bodyIndices[i];
        convertVector(this->newPositions[i], newPositions[bodyIndex]);
        convertQuaternion(this->newOrientations[i], newOrientations[bodyIndex]);
      }
    }

    const Quanta::Matrix4* Interpolater::getTransforms() const {
      return transforms;
    }
  }
}
