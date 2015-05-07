#ifndef FIXIE_TRANSFORM_FACTORY_H
#define FIXIE_TRANSFORM_FACTORY_H

#include "Fixie/Num.h"
#include "Fixie/Quaternion.h"
#include "Fixie/Vector3.h"
#include "Fixie/Matrix4.h"

namespace Fixie {
  namespace TransformFactory {
    Matrix4 translation(Vector3 translation);
    Quaternion rotation(Vector3 axis, Num angle);
  }
}

#endif
