#include "Quanta/Math/Vector3.h"
#include "Quanta/Geometry/Plane.h"
#include "Quanta/Geometry/Frustum.h"
#include "Rendering/Config.h"
#include "Rendering/FrustumInfo.h"
#include "Rendering/Frustum.h"

namespace Rendering {
  namespace Frustum {
    void calcInfo(FrustumInfo &info, float aspectRatio) {
      info.nearWidth = tan(Config::perspective.fieldOfView/2)*2*Config::perspective.near;
      info.nearHeight = info.nearWidth/aspectRatio;
      info.farWidth = info.nearWidth*(Config::perspective.far/Config::perspective.near);
      info.farHeight = info.farWidth/aspectRatio;
    }

    void calcFrustum(const FrustumInfo &info, Quanta::Frustum &frustum) {
      Quanta::Vector3 up(0, 1, 0);
      Quanta::Vector3 right(1, 0, 0);

      Quanta::Plane &nearPlane = frustum.planes[Quanta::Frustum::Near];
      nearPlane.position = Quanta::Vector3(0, 0, Config::perspective.near);
      nearPlane.normal = Quanta::Vector3(0, 0, 1);

      Quanta::Plane &farPlane = frustum.planes[Quanta::Frustum::Far];
      farPlane.position = Quanta::Vector3(0, 0, Config::perspective.far);
      farPlane.normal = Quanta::Vector3(0, 0, -1);

      Quanta::Plane &topPlane = frustum.planes[Quanta::Frustum::Top];
      topPlane.position = Quanta::Vector3::zero();
      topPlane.normal = Quanta::Vector3::cross(right, Quanta::Vector3(0, info.nearHeight/2, Config::perspective.near).getNormalized());

      Quanta::Plane &bottomPlane = frustum.planes[Quanta::Frustum::Bottom];
      bottomPlane.position = Quanta::Vector3::zero();
      bottomPlane.normal = Quanta::Vector3(topPlane.normal[0], topPlane.normal[1]*-1, topPlane.normal[2]);

      Quanta::Plane &leftPlane = frustum.planes[Quanta::Frustum::Left];
      leftPlane.position = Quanta::Vector3::zero();
      leftPlane.normal = Quanta::Vector3::cross(up, Quanta::Vector3(-info.nearWidth/2, 0, Config::perspective.near)).getNormalized();

      Quanta::Plane &rightPlane = frustum.planes[Quanta::Frustum::Right];
      rightPlane.position = Quanta::Vector3::zero();
      rightPlane.normal = Quanta::Vector3(leftPlane.normal[0]*-1, leftPlane.normal[1], leftPlane.normal[2]);
    }
  }
}
