#include "Core/Error.h"
#include "Rendering/ObjectIDCaster.h"
#include "Rendering/Renderer.h"

namespace Rendering {
  Renderer::Renderer() :
  commandBuilder(commandSorter, animatedMeshInstanceList, cameraTransform) { }

  void Renderer::initialize() {
    backend.initialize();
  }

  AnimatedMeshIndex Renderer::createAnimatedMesh(const AnimatedVertex *vertices, const size_t vertexCount, const uint16_t *indices, const size_t indexCount) {
    return backend.createAnimatedMesh(vertices, vertexCount, indices, indexCount);
  }

  void Renderer::createAnimatedMeshInstance(AnimatedMeshIndex meshIndex, TransformIndex transformIndex) {
    AnimatedMeshInstanceIndex meshInstanceIndex = animatedMeshInstanceList.create(meshIndex, transformIndex);
    ObjectIndex objectIndex = objectList.create(ObjectType::AnimatedMeshInstance, ObjectIDCaster::createByAnimatedMeshInstanceIndex(meshInstanceIndex));
    culler.create(objectIndex); // todo: pass bounding data also
  }

  void Renderer::draw() {
    backend.clear();
    uint16_t visibleCount = culler.cull(visibleBuffer); // TODO: Pass frustrum data also
    commandBuilder.build(objectList.getObjects(), visibleBuffer, visibleCount);
    commandSorter.sort();
    commandMerger.merge(commandSorter);
    backend.draw(commandMerger.getBuffer(), commandMerger.getCount());
    commandSorter.clear();
  }

  void Renderer::setTransforms(const Quanta::Matrix4 *transforms) {
    commandBuilder.transforms = transforms;
  }

  void Renderer::setPoses(const Pose *poses) {
    commandBuilder.poses = poses;
  }
}
