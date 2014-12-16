#include "FrameInterpolator.h"

void FrameInterpolator::initialize(const Quanta::Vector3 *positions, const Quanta::Quaternion *orientations) {
  for(uint8_t i=0; bodyCount>i; i++) {
    Physics::DynamicBodyIndex bodyIndex = bodyIndices[i];
    oldPositions[i] = positions[bodyIndex];
    newPositions[i] = positions[bodyIndex];
    newOrientations[i] = orientations[bodyIndex];
    oldOrientations[i] = orientations[bodyIndex];
  }
  interpolate(0);
}

void FrameInterpolator::interpolate(double progress) {
  for(uint8_t i=0; bodyCount>i; i++) {
    Quanta::Vector3 position = oldPositions[i] + (newPositions[i]-oldPositions[i])*progress;
    Quanta::Matrix4 translation = Quanta::TransformFactory3D::translation(position);
    Quanta::Quaternion orientation = Quanta::Quaternion::slerp(oldOrientations[i], newOrientations[i], progress);
    transforms[i] = translation * static_cast<Quanta::Matrix4>(orientation);
  }
}

uint8_t FrameInterpolator::createInterpolation(Physics::DynamicBodyIndex body) {
  bodyIndices[bodyCount] = body;
  return bodyCount++;
}

void FrameInterpolator::reload(const Quanta::Vector3 *newPositions, const Quanta::Quaternion *newOrientations) {
  for(uint8_t i=0; bodyCount>i; i++) {
    oldPositions[i] = this->newPositions[i];
    oldOrientations[i] = this->newOrientations[i];
    Physics::DynamicBodyIndex bodyIndex = bodyIndices[i];
    this->newPositions[i] = newPositions[bodyIndex];
    this->newOrientations[i] = newOrientations[bodyIndex];
  }
}

const Quanta::Matrix4* FrameInterpolator::getTransforms() const {
  return transforms;
}
