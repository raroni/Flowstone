#include "Quanta/Geometry/TransformFactory3D.h"
#include "TorchManager.h"

void TorchManager::initialize() {
  const float woodHeight = 0.4;
  const float width = 0.1;
  const float fireHeight = 0.15;

  const float halfWidth = width*0.5;
  const float totalHeight = woodHeight + fireHeight;

  Rendering::StaticVertex vertices[] = {
    { { halfWidth, 0, -halfWidth } },
    { { -halfWidth, 0, -halfWidth } },
    { { -halfWidth, 0, halfWidth } },
    { { halfWidth, 0, halfWidth } },

    { { halfWidth, woodHeight, -halfWidth } },
    { { -halfWidth, woodHeight, -halfWidth } },
    { { -halfWidth, woodHeight, halfWidth } },
    { { halfWidth, woodHeight, halfWidth } },

    { { halfWidth, totalHeight, -halfWidth } },
    { { -halfWidth, totalHeight, -halfWidth } },
    { { -halfWidth, totalHeight, halfWidth } },
    { { halfWidth, totalHeight, halfWidth } },
  };

  uint16_t indices[] = {
    // bottom
    0, 1, 2, 0, 2, 3,

    // wood sides
    5, 1, 0, 5, 0, 4,
    6, 2, 1, 6, 1, 5,
    7, 3, 2, 7, 2, 6,
    4, 0, 3, 4, 3, 7,

    // fire sides
    9, 5, 4, 9, 4, 8,
    10, 6, 5, 10, 5, 9,
    11, 7, 6, 11, 6, 10,
    8, 4, 7, 8, 7, 10,

    // top
    10, 9, 8, 10, 8, 11
  };

  Rendering::Shape shapes[] = {
    { { 0.47, 0.29, 0.17 }, 0, 10 },
    { { 1.0, 0.63, 0.05 }, 10, 10 }
  };

  Rendering::MeshInfo info;
  info.vertexCount = sizeof(vertices)/sizeof(Rendering::StaticVertex);
  info.indexCount = sizeof(indices)/sizeof(uint16_t);
  info.shapeCount = 2;

  meshIndex = renderer.createStaticMesh(info, vertices, indices, shapes);
}

void TorchManager::create(float x, float z) {
  /*
  Disabled while playing with self-illumination
  Rendering::PointLightIndex light = renderer.createPointLight();
  renderer.updatePointLightPosition(light, { x, 0.4, z-0.3f });
  */

  Rendering::StaticMeshInstanceIndex mesh = renderer.createStaticMeshInstance(meshIndex);
  Quanta::Matrix4 transform = Quanta::TransformFactory3D::translation({ x, 0, z });

  renderer.updateStaticMeshTransform(mesh, transform);
}
