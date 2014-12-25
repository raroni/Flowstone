#include "Quanta/Math/Vector3.h"
#include "Quanta/Math/Vector4.h"
#include "Quanta/Geometry/Transformer.h"
#include "Quanta/Geometry/TransformFactory3D.h"
#include "Quanta/ProjectionFactory.h"
#include "Rendering/LightTransforms.h"
#include "Rendering/Config.h"

namespace Rendering {
  namespace LightTransforms {
    void calc(
      const FrustumInfo &frustumInfo,
      const Quanta::Matrix4 &cameraViewWorldTransform,
      const Quanta::Vector3 &lightDirection,
      Quanta::Matrix4 &lightWorldView,
      Quanta::Matrix4 &lightViewClipTransform
    ) {
      enum Corners { // todo move this enum declaration out of runtime
        NearTopLeft,
        NearTopRight,
        NearBottomLeft,
        NearBottomRight,
        FarTopLeft,
        FarTopRight,
        FarBottomLeft,
        FarBottomRight
      };
      Quanta::Vector3 corners[8];
      corners[NearTopLeft] = Quanta::Vector3(-frustumInfo.nearWidth*0.5, frustumInfo.nearHeight*0.5, Config::perspective.near);
      corners[NearTopRight] = Quanta::Vector3(corners[NearTopLeft][0]*-1, corners[NearTopLeft][1], corners[NearTopLeft][2]);
      corners[NearBottomLeft] = Quanta::Vector3(corners[NearTopLeft][0], corners[NearTopLeft][1]*-1, corners[NearTopLeft][2]);
      corners[NearBottomRight] = Quanta::Vector3(corners[NearBottomLeft][0]*-1, corners[NearBottomLeft][1], corners[NearBottomLeft][2]);
      corners[FarTopLeft] = Quanta::Vector3(frustumInfo.farWidth*0.5, frustumInfo.farHeight*0.5, Config::perspective.far);
      corners[FarTopRight] = Quanta::Vector3(corners[FarTopLeft][0]*-1, corners[FarTopLeft][1], corners[FarTopLeft][2]);
      corners[FarBottomLeft] = Quanta::Vector3(corners[FarTopLeft][0], corners[FarTopLeft][1]*-1, corners[FarTopLeft][2]);
      corners[FarBottomRight] = Quanta::Vector3(corners[FarBottomLeft][0]*-1, corners[FarBottomLeft][1], corners[FarBottomLeft][2]);
      Quanta::Vector3 centroid = Quanta::Vector3::zero();
      for(uint8_t i=0; 8>i; i++) {
        Quanta::Vector4 temp(corners[i][0], corners[i][1], corners[i][2], 1);
        Quanta::Transformer::updateVector4(temp, cameraViewWorldTransform);
        corners[i] = Quanta::Vector3(temp[0], temp[1], temp[2]);
        centroid += corners[i];
      }
      centroid *= 0.125;
      Quanta::Vector3 position = centroid - lightDirection*Config::perspective.far;
      Quanta::Vector3 up(0, 1, 0);
      lightWorldView = Quanta::TransformFactory3D::lookAt(position, centroid, up);

      for(uint8_t i=0; 8>i; i++) {
        Quanta::Vector4 temp(corners[i][0], corners[i][1], corners[i][2], 1);
        Quanta::Transformer::updateVector4(temp, lightWorldView);
        corners[i] = Quanta::Vector3(temp[0], temp[1], temp[2]);
      }

      Quanta::Vector3 mins = corners[0];
      Quanta::Vector3 maxes = corners[0];
      for(uint8_t i=1; 8>i; i++) {
        mins[0] = fminf(mins[0], corners[i][0]);
        mins[1] = fminf(mins[1], corners[i][1]);
        mins[2] = fminf(mins[2], corners[i][2]);
        maxes[0] = fmaxf(maxes[0], corners[i][0]);
        maxes[1] = fmaxf(maxes[1], corners[i][1]);
        maxes[2] = fmaxf(maxes[2], corners[i][2]);
      }

      lightViewClipTransform = Quanta::ProjectionFactory::ortho(mins[0], maxes[0], mins[1], maxes[1], mins[2]-5.0, maxes[2]);
    }
  }
}
