#include "Core/Physics/Engine.h"

namespace Physics {
  const double Engine::stepDuration = 0.03;

  uint8_t Engine::createTransform() {
    return 0;
  }

  void Engine::createRigidBody(uint8_t transformID) {

  }

  void Engine::createSphereCollider(uint8_t transformID) {

  }

  void Engine::simulate() {

  }

  const Quanta::Vector3* Engine::getPositions() const {
    return positions;
  }

  const Quanta::Quaternion* Engine::getOrientations() const {
    return orientations;
  }
}
