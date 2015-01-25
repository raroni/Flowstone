#include <stddef.h>
#include <string.h>
#include "Quanta/Geometry/Transformer.h"
#include "Quanta/ProjectionFactory.h"
#include "Quanta/Math/Vector4.h"
#include "Core/Error.h"
#include "Rendering/Shadow.h"
#include "Rendering/GeometryPass.h"
#include "Rendering/SSAO.h"
#include "Rendering/MergePass.h"
#include "Rendering/CommandStream.h"
#include "Rendering/PointLights.h"
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
    SSAO::initialize();
    MergePass::initialize();
    Shadow::initialize();
    PointLights::initialize();
  }

  BoneMeshIndex WorldRenderer::createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
    return boneMeshRegistry.create(vertices, vertexCount, indices, indexCount);
  }

  void WorldRenderer::setPrimaryLightColor(Quanta::Vector3 color) {
    MergePass::primaryLightColor = color;
  }

  BoneMeshInstanceIndex WorldRenderer::createBoneMeshInstance(BoneMeshIndex meshIndex) {
    BoneMesh mesh = boneMeshRegistry.get(meshIndex);
    return BoneMeshInstances::create(meshIndex, mesh.boundingRadius);
  }

  PointLightIndex WorldRenderer::createPointLight() {
    return PointLights::create();
  }

  void WorldRenderer::updatePointLightPosition(PointLightIndex index, const Quanta::Vector3 &position) {
    PointLights::updatePosition(index, position);
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

  void WorldRenderer::updateResolution(Resolution resolution) {
    this->resolution = resolution;
    float aspectRatio = static_cast<float>(resolution.width)/resolution.height;
    Frustum::calcInfo(frustumInfo, aspectRatio);
    Frustum::calcFrustum(frustumInfo, localFrustum);
    calcViewClipTransform();
    SSAO::handleResolutionChange(resolution);
  }

  void WorldRenderer::writeCommands(CommandStream &stream) {
    Quanta::Matrix4 viewWorldTransform = cameraTransform.calcMatrix();
    Quanta::Matrix4 worldViewTransform = cameraTransform.calcInverseMatrix();
    Quanta::Matrix4 clipWorldTransform = (viewClipTransform*worldViewTransform).getInverted();

    Quanta::Frustum frustum = localFrustum;
    Quanta::Transformer::updateFrustum(frustum, viewWorldTransform);

    LightTransforms::calc(
      frustumInfo,
      viewWorldTransform,
      primaryLightDirection,
      primaryLightTransforms.worldView,
      primaryLightTransforms.viewClip
    );
    culler.cull(frustum, drawSet);
    stream.writeEnableDepthTest();
    stream.writeViewportSet(Config::shadowMapSize, Config::shadowMapSize);
    Shadow::write(stream, boneMeshRegistry, drawSet, primaryLightTransforms.worldView, primaryLightTransforms.viewClip);
    stream.writeViewportSet(resolution.width, resolution.height);
    writeGlobalUniformUpdate(stream, worldViewTransform);
    GeometryPass::write(stream, drawSet, boneMeshRegistry);

    stream.writeDisableDepthTest();

    SSAO::write(stream, resolution, worldViewTransform, viewClipTransform, clipWorldTransform);

    stream.writeRenderTargetSet(0);

    stream.writeClear(static_cast<Backend::ClearBitMask>(Backend::ClearBit::Color));

    MergePass::write(
      stream,
      (viewClipTransform*worldViewTransform).getInverted(),
      primaryLightTransforms.worldView,
      primaryLightTransforms.viewClip,
      primaryLightDirection,
      secondaryLightDirection
    );

    PointLights::write(stream);

    drawSet.clear();
  }

  void WorldRenderer::writeGlobalUniformUpdate(CommandStream &stream, const Quanta::Matrix4 &worldViewTransform) {
    Backend::BufferHandle globalBuffer = Buffers::handles[static_cast<size_t>(BufferName::Global1)];
    stream.writeBufferSet(Backend::BufferTarget::Uniform, globalBuffer);

    const size_t matrixSize = sizeof(float)*16;
    const size_t totalSize = matrixSize*2;
    char data[totalSize];
    memcpy(data, &viewClipTransform.components, matrixSize);
    memcpy(data+matrixSize, &worldViewTransform.components, matrixSize);
    stream.writeBufferWrite(Backend::BufferTarget::Uniform, totalSize, data);

    stream.writeBufferSet(Backend::BufferTarget::Uniform, 0);
  }

  void WorldRenderer::calcViewClipTransform() {
    float aspectRatio = static_cast<float>(resolution.width)/(resolution.height);
    viewClipTransform = Quanta::ProjectionFactory::perspective(Config::perspective.fieldOfView, aspectRatio, Config::perspective.near, Config::perspective.far);
  }
}
