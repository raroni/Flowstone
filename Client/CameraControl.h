#ifndef CLIENT_CAMERA_CONTROL_H
#define CLIENT_CAMERA_CONTROL_H

#include "Quanta/Geometry/Transform.h"
#include "Client/Keyboard.h"

namespace Client {
  namespace CameraControl {
    void initialize(Quanta::Transform *transform);
    void update(double timeDelta, const Keyboard *keyboard, Quanta::Transform *transform);
  }
}

#endif
