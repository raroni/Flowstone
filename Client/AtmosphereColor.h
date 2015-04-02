#ifndef CLIENT_ATMOSPHERE_COLOR_H
#define CLIENT_ATMOSPHERE_COLOR_H

#include <stdint.h>
#include "Quanta/Math/Vector3.h"

namespace Client {
  class AtmosphereColor {
    const static uint16_t count = 1024;
    Quanta::Vector3 colors[count];
  public:
    AtmosphereColor();
    const Quanta::Vector3& get(float progress);
  };
}

#endif
