#include <stddef.h>
#include <string.h>
#include "Quanta/Geometry/Transformer.h"
#include "Quanta/ProjectionFactory.h"
#include "Quanta/Math/Vector4.h"
#include "Core/Error.h"
#include "Rendering/ShadowPass.h"
#include "Rendering/GeometryPass.h"
#include "Rendering/MergePass.h"
#include "Rendering/CommandStream.h"
#include "Rendering/LightTransforms.h"
#include "Rendering/Buffers.h"
#include "Rendering/BufferName.h"
#include "Rendering/Backend/ClearBit.h"
#include "Rendering/StaticMeshInstances.h"
#include "Rendering/StaticMeshes.h"
#include "Rendering/BoneMeshInstances.h"
#include "Rendering/Frustum.h"
#include "Rendering/WorldRenderer.h"

namespace Rendering {
  void WorldRenderer::initialize() {
    Frustum::calcInfo(frustumInfo);
    Frustum::calcFrustum(frustumInfo, localFrustum);
    calcViewClipTransform();
  }

  BoneMeshIndex WorldRenderer::createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
    return boneMeshRegistry.create(vertices, vertexCount, indices, indexCount);
  }

  BoneMeshInstanceIndex WorldRenderer::createBoneMeshInstance(BoneMeshIndex meshIndex) {
    BoneMesh mesh = boneMeshRegistry.get(meshIndex);
    return BoneMeshInstances::create(meshIndex, mesh.boundingRadius);
  }

  BoneMeshInstance WorldRenderer::getBoneMeshInstance(BoneMeshInstanceIndex index) {
    return BoneMeshInstances::get(index);
  }

  StaticMeshIndex WorldRenderer::createStaticMesh(MeshInfo info, const StaticVertex *vertices, const uint16_t *indices, const Shape *shapes) {
    return StaticMeshes::create(info, vertices, indices, shapes);
  }

  void WorldRenderer::updateStaticMeshTransform(StaticMeshInstanceIndex index, const Quanta::Matrix4 &transform) {
    StaticMeshInstances::updateTransform(index, transform);
  }

  StaticMeshInstanceIndex WorldRenderer::createStaticMeshInstance(StaticMeshIndex index) {
    const StaticMesh& mesh = StaticMeshes::get(index);
    return StaticMeshInstances::create(index, mesh.boundingRadius);
  }

  void WorldRenderer::updateResolution(uint16_t width, uint16_t height) {
    resolution.width = width;
    resolution.height = height;
  }

  void WorldRenderer::writeCommands(CommandStream &stream) {
    Quanta::Matrix4 viewWorldTransform = cameraTransform.calcMatrix();
    Quanta::Matrix4 worldViewTransform = cameraTransform.calcInverseMatrix();

    Quanta::Frustum frustum = localFrustum;
    Quanta::Transformer::updateFrustum(frustum, viewWorldTransform);

    LightTransforms::calc(frustumInfo, viewWorldTransform, lightDirection, lightTransforms.worldView, lightTransforms.viewClip);
    culler.cull(frustum, drawSet);
    stream.writeEnableDepthTest();
    stream.writeViewportSet(Config::shadowMapSize, Config::shadowMapSize);
    ShadowPass::write(stream, boneMeshRegistry, drawSet, lightTransforms.viewClip, lightTransforms.worldView);
    stream.writeViewportSet(800, 600);
    writeGlobalUniformUpdate(stream, worldViewTransform);
    GeometryPass::write(stream, drawSet, boneMeshRegistry);

    stream.writeRenderTargetSet(0);
    stream.writeDisableDepthTest();

    stream.writeClear(static_cast<Backend::ClearBitMask>(Backend::ClearBit::Color));

    MergePass::write(
      stream,
      viewClipTransform*worldViewTransform,
      lightTransforms.viewClip*lightTransforms.worldView,
      lightDirection
    );

    drawSet.clear();
  }

  void WorldRenderer::writeGlobalUniformUpdate(CommandStream &stream, const Quanta::Matrix4 &worldViewTransform) {
    Backend::BufferHandle globalBuffer = Buffers::handles[static_cast<size_t>(BufferName::Global1)];
    stream.writeBufferSet(Backend::BufferTarget::Uniform, globalBuffer);

    Quanta::Vector3 inverseLightDirection = lightDirection.getNegated();

    const size_t matrixSize = sizeof(float)*16;
    const size_t vectorSize = sizeof(float)*3;
    const size_t totalSize = matrixSize*2+vectorSize;
    char data[totalSize];
    memcpy(data, &viewClipTransform.components, matrixSize);
    memcpy(data+matrixSize, &worldViewTransform.components, matrixSize);
    memcpy(data+matrixSize*2, &inverseLightDirection.components, vectorSize);
    stream.writeBufferWrite(Backend::BufferTarget::Uniform, totalSize, data);

    stream.writeBufferSet(Backend::BufferTarget::Uniform, 0);
  }

  void WorldRenderer::calcViewClipTransform() {
    float aspectRatio = static_cast<float>(resolution.width)/(resolution.height);
    viewClipTransform = Quanta::ProjectionFactory::perspective(Config::perspective.fieldOfView, aspectRatio, Config::perspective.near, Config::perspective.far);
  }
}
