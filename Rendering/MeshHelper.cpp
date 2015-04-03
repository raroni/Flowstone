#include "Rendering/MeshHelper.h"

namespace Rendering {
  namespace MeshHelper {
    float calcBoundingRadius(const Quanta::Vector3 *positions, uint16_t count) {
      uint16_t maxIndex = 0;
      float maxSquaredLength = 0;
      for(uint16_t i=0; count>i; i++) {
        float squaredLength = positions[i].getSquaredLength();
        if(squaredLength > maxSquaredLength) {
          maxSquaredLength = squaredLength;
          maxIndex = i;
        }
      }
      return positions[maxIndex].getLength();
    }
  }
}
