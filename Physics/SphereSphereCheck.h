#ifndef PHYSICS_SPHERE_SPHERE_CHECK_H
#define PHYSICS_SPHERE_SPHERE_CHECK_H

namespace Physics {
  struct SphereSphereCheck {
    bool positive;
    BodyHandle bodyHandle1;
    BodyHandle bodyHandle2;
    Fixie::Vector3 separation;
  };
}

#endif
