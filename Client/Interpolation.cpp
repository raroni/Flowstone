#include "Quanta/Geometry/TransformFactory3D.h"
#include "Client/MathConversion.h"
#include "Client/Interpolation.h"

namespace Client {
  namespace Interpolation {
    using namespace MathConversion;

    const uint16_t max = 128;
    Quanta::Vector3 oldPositions[max];
    Quanta::Vector3 newPositions[max];
    Quanta::Quaternion oldOrientations[max];
    Quanta::Quaternion newOrientations[max];
    Quanta::Matrix4 transforms[max];
    Physics::BodyHandle bodyHandles[max];
    uint8_t count = 0;

    void prepare(const Physics::BodyList &bodies) {
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

    void interpolate(double progress) {
      for(uint8_t i=0; count>i; i++) {
        Quanta::Vector3 position = oldPositions[i] + (newPositions[i]-oldPositions[i])*progress;
        Quanta::Matrix4 translation = Quanta::TransformFactory3D::translation(position);
        Quanta::Quaternion orientation = Quanta::Quaternion::slerp(oldOrientations[i], newOrientations[i], progress);
        transforms[i] = translation * static_cast<Quanta::Matrix4>(orientation);
      }
    }

    InterpolationHandle createInterpolation(Physics::BodyHandle body) {
      assert(max != count);
      bodyHandles[count] = body;
      return count++;
    }

    void reload(const Physics::BodyList &bodies) {
      for(uint8_t i=0; count>i; i++) {
        Physics::BodyHandle handle = bodyHandles[i];
        Physics::ConstBody body = bodies.get(handle);

        oldPositions[i] = newPositions[i];
        oldOrientations[i] = newOrientations[i];
        convertVector(newPositions[i], *(body.position));
        convertQuaternion(newOrientations[i], *(body.orientation));
      }
    }

    const Quanta::Matrix4* getTransforms() {
      return transforms;
    }
  }
}
