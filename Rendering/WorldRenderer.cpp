#include <stddef.h>
#include <string.h>
#include "Quanta/Geometry/Transformer.h"
#include "Quanta/ProjectionFactory.h"
#include "Quanta/Math/Vector4.h"
#include "Misc/Error.h"
#include "Rendering/Shadow.h"
#include "Rendering/GeometryPass.h"
#include "Rendering/SSAO.h"
#include "Rendering/MergePass.h"
#include "Rendering/CommandStream.h"
#include "Rendering/PointLights.h"
#include "Rendering/PointLightPass.h"
#include "Rendering/LightTransforms.h"
#include "Rendering/Buffers.h"
#include "Rendering/BufferName.h"
#include "SysGFX/ClearBit.h"
#include "Rendering/StaticMeshDraws.h"
#include "Rendering/StaticMeshes.h"
#include "Rendering/BoneMeshDraws.h"
#include "Rendering/Frustum.h"
#include "Rendering/WorldRenderer.h"

namespace Rendering {
  void WorldRenderer::initialize() {
    SSAO::initialize();
    MergePass::initialize();
    Shadow::initialize();
    PointLightPass::initialize();
  }

  BoneMeshIndex WorldRenderer::createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
    return boneMeshRegistry.create(vertices, vertexCount, indices, indexCount);
  }

  void WorldRenderer::setPrimaryLightColor(Quanta::Vector3 color) {
    MergePass::primaryLightColor = color;
  }

  BoneMeshDrawHandle WorldRenderer::createBoneMeshDraw(BoneMeshIndex meshIndex) {
    BoneMesh mesh = boneMeshRegistry.get(meshIndex);
    return BoneMeshDraws::create(meshIndex, mesh.boundingRadius);
  }

  PointLightHandle WorldRenderer::createPointLight() {
    return PointLights::create();
  }

  void WorldRenderer::updatePointLightPosition(PointLightHandle handle, const Quanta::Vector3 &position) {
    PointLights::updatePosition(handle, position);
  }

  BoneMeshDraw WorldRenderer::getBoneMeshDraw(BoneMeshDrawHandle handle) {
    return BoneMeshDraws::get(handle);
  }

  StaticMeshIndex WorldRenderer::createStaticMesh(MeshInfo info, const StaticVertex *vertices, const uint16_t *indices, const Shape *shapes) {
    return StaticMeshes::create(info, vertices, indices, shapes);
  }

  void WorldRenderer::updateStaticMeshTransform(StaticMeshDrawHandle handle, const Quanta::Matrix4 &transform) {
    StaticMeshDraws::updateTransform(handle, transform);
  }

  StaticMeshDrawHandle WorldRenderer::createStaticMeshDraw(StaticMeshIndex index) {
    const StaticMesh& mesh = StaticMeshes::get(index);
    return StaticMeshDraws::create(index, mesh.boundingRadius);
  }

  void WorldRenderer::updateResolution(Resolution resolution) {
    this->resolution = resolution;
    float aspectRatio = static_cast<float>(resolution.width)/resolution.height;
    Frustum::calcInfo(frustumInfo, aspectRatio);
    Frustum::calcFrustum(frustumInfo, localFrustum);
    calcViewClipTransform();
    SSAO::handleResolutionChange(resolution);
    PointLightPass::handleResolutionChange(resolution);
  }

  void WorldRenderer::writeCommands(CommandStream &stream) {
    struct {
      Quanta::Matrix4 viewWorld;
      Quanta::Matrix4 worldView;
      Quanta::Matrix4 clipWorld;
    } cameraTransforms = {
      cameraTransform.calcMatrix(),
      cameraTransform.calcInverseMatrix()
    };
    cameraTransforms.clipWorld = (cameraViewClipTransform*cameraTransforms.worldView).getInverted();

    Quanta::Frustum frustum = localFrustum;
    Quanta::Transformer::updateFrustum(frustum, cameraTransforms.viewWorld);

    LightTransforms::calc(
      frustumInfo,
      cameraTransforms.viewWorld,
      primaryLightDirection,
      primaryLightTransforms.worldView,
      primaryLightTransforms.viewClip
    );
    culler.cull(frustum, drawSet);
    stream.writeEnableDepthTest();
    stream.writeViewportSet(Config::shadowMapSize, Config::shadowMapSize);
    Shadow::write(stream, boneMeshRegistry, drawSet, primaryLightTransforms.worldView, primaryLightTransforms.viewClip);
    stream.writeViewportSet(resolution.width, resolution.height);
    writeGlobalUniformUpdate(stream, cameraTransforms.worldView);
    GeometryPass::write(stream, drawSet, boneMeshRegistry);

    stream.writeDisableDepthTest();

    SSAO::write(stream, resolution, cameraTransforms.clipWorld);

    stream.writeRenderTargetSet(0);

    stream.writeClear(static_cast<SysGFX::ClearBitMask>(SysGFX::ClearBit::Color));

    MergePass::write(
      stream,
      cameraTransforms.clipWorld,
      primaryLightTransforms.worldView,
      primaryLightTransforms.viewClip,
      primaryLightDirection,
      secondaryLightDirection
    );

    PointLightPass::write(stream, drawSet.pointLightSet, cameraTransforms.clipWorld);

    drawSet.clear();
  }

  void WorldRenderer::writeGlobalUniformUpdate(CommandStream &stream, const Quanta::Matrix4 &worldViewTransform) {
    SysGFX::BufferHandle globalBuffer = Buffers::handles[static_cast<size_t>(BufferName::Global1)];
    stream.writeBufferSet(SysGFX::BufferTarget::Uniform, globalBuffer);

    const size_t matrixSize = sizeof(float)*16;
    const size_t totalSize = matrixSize*2;
    char data[totalSize];
    memcpy(data, &cameraViewClipTransform.components, matrixSize);
    memcpy(data+matrixSize, &worldViewTransform.components, matrixSize);
    stream.writeBufferWrite(SysGFX::BufferTarget::Uniform, totalSize, data);

    stream.writeBufferSet(SysGFX::BufferTarget::Uniform, 0);
  }

  void WorldRenderer::calcViewClipTransform() {
    float aspectRatio = static_cast<float>(resolution.width)/(resolution.height);
    cameraViewClipTransform = Quanta::ProjectionFactory::perspective(Config::perspective.fieldOfView, aspectRatio, Config::perspective.near, Config::perspective.far);
  }
}
