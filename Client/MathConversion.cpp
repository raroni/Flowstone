#include "Client/MathConversion.h"

namespace Client {
  namespace MathConversion {
    void convertVector(Quanta::Vector3 &o, const Fixie::Vector3 &i) {
      o[0] = i[0];
      o[1] = i[1];
      o[2] = i[2];
    }

    void convertQuaternion(Quanta::Quaternion &o, const Fixie::Quaternion &i) {
      o.real = i.real;
      convertVector(o.imaginaries, i.imaginaries);
    }

    void convertMatrix(Quanta::Matrix4 &o, const Fixie::Matrix4 &i) {
      for(uint8_t n=0; n<16; ++n) {
        o[n] = i[n];
      }
    }
  }
}
