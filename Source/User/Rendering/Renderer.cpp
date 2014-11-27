#include "Rendering/Renderer.h"
#include "Rendering/ShaderPrograms.h"
#include "Rendering/Backend/Backend.h"

namespace Rendering {
  void Renderer::initialize() {
    ShaderPrograms::initialize();
  }

  BoneMeshIndex Renderer::createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
    return worldRenderer.createBoneMesh(vertices, vertexCount, indices, indexCount);
  }

  void Renderer::createBoneMeshInstance(BoneMeshIndex meshIndex, TransformIndex transformIndex) {
    worldRenderer.createBoneMeshInstance(meshIndex, transformIndex);
  }

  void Renderer::draw() {
  }

  void Renderer::setTransforms(const Quanta::Matrix4 *transforms) {

  }

  void Renderer::setPoses(const Pose *poses) {

  }
}
