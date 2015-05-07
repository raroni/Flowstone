#include "Client/CameraControl.h"

namespace Client {
  namespace CameraControl {
    using namespace Quanta;

    Vector3 velocity = Vector3::zero();

    void initialize(Transform *transform) {
      transform->position[0] = 2;
      transform->position[1] = 6;
      transform->position[2] = -1.75;
      transform->rotateX(1);
    }

    void update(const double timeDelta, const Keyboard *keyboard, Quanta::Transform *transform) {
      Vector3 keyboardDirection = Vector3::zero();
      if(keyboard->isDown(SysKey::Key::D)) {
        keyboardDirection[0] += 1;
      }
      if(keyboard->isDown(SysKey::Key::A)) {
        keyboardDirection[0] -= 1;
      }
      if(keyboard->isDown(SysKey::Key::W)) {
        keyboardDirection[2] += 1;
      }
      if(keyboard->isDown(SysKey::Key::S)) {
        keyboardDirection[2] -= 1;
      }

      Vector3 force = Vector3::zero();
      force += velocity*-8;
      if(!keyboardDirection.isZero()) {
        keyboardDirection.normalize();
        force += keyboardDirection*50;
      }

      velocity += force*timeDelta;
      transform->position += velocity*timeDelta;
    }
  }
}
