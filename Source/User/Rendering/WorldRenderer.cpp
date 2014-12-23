#include <stddef.h>
#include <string.h>
#include <math.h>
#include "Quanta/ProjectionFactory.h"
#include "Core/Error.h"
#include "Quanta/Math/Matrix4.h"
#include "Quanta/Math/Vector4.h"
#include "Quanta/Geometry/Transformer.h"
#include "Rendering/BoneMeshInstances.h"
#include "Rendering/BoneMeshInstance.h"
#include "Rendering/Commands.h"
#include "Rendering/StaticMeshes.h"
#include "Rendering/StaticMeshInstances.h"
#include "Rendering/Programs.h"
#include "Rendering/Uniforms.h"
#include "Rendering/FullscreenQuad.h"
#include "Rendering/Textures.h"
#include "Rendering/RenderTargets.h"
#include "Rendering/ProgramName.h"
#include "Rendering/Backend/ClearBit.h"
#include "Rendering/Buffers.h"
#include "Rendering/CullGroupNames.h"
#include "Rendering/BufferName.h"
#include "Rendering/Backend/Functions.h"
#include "Rendering/CommandStream.h"
#include "Rendering/WorldRenderer.h"
#include "Quanta/Geometry/TransformFactory3D.h"

namespace Rendering {
  void WorldRenderer::initialize() {
    culler.configureGroup(CullGroupNames::Bone, BoneMeshInstances::transforms, BoneMeshInstances::boundingRadii);
    culler.configureGroup(CullGroupNames::Static, StaticMeshInstances::transforms, StaticMeshInstances::boundingRadii);
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

  // TODO: No need to calculate this over and over
  Quanta::Frustum WorldRenderer::calcFrustum() const {
    Quanta::Frustum frustum;

    float nearWidth = tan(Config::perspective.fieldOfView/2)*2*Config::perspective.near;
    float nearHeight = nearWidth/(800.0/600.0); // TODO: replace with real aspect ratio
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
    topPlane.normal = Quanta::Vector3::cross(right, Quanta::Vector3(0, nearHeight/2, Config::perspective.near).getNormalized());

    Quanta::Plane &bottomPlane = frustum.planes[Quanta::Frustum::Bottom];
    bottomPlane.position = Quanta::Vector3::zero();
    bottomPlane.normal = Quanta::Vector3(topPlane.normal[0], topPlane.normal[1]*-1, topPlane.normal[2]);

    Quanta::Plane &leftPlane = frustum.planes[Quanta::Frustum::Left];
    leftPlane.position = Quanta::Vector3::zero();
    leftPlane.normal = Quanta::Vector3::cross(up, Quanta::Vector3(-nearWidth/2, 0, Config::perspective.near)).getNormalized();

    Quanta::Plane &rightPlane = frustum.planes[Quanta::Frustum::Right];
    rightPlane.position = Quanta::Vector3::zero();
    rightPlane.normal = Quanta::Vector3(leftPlane.normal[0]*-1, leftPlane.normal[1], leftPlane.normal[2]);

    Quanta::Transformer::updateFrustum(frustum, cameraTransform.getMatrix());
    return frustum;
  }

  void WorldRenderer::writeCommands(CommandStream &stream) {
    calcLightTransforms();
    buildDrawSet();
    stream.writeEnableDepthTest();
    stream.writeViewportSet(Config::shadowMapSize, Config::shadowMapSize);
    writeShadowMap(stream);
    stream.writeViewportSet(800, 600);
    writeGlobalUniformUpdate(stream);
    stream.writeRenderTargetSet(RenderTargets::handles.geometry);
    stream.writeClear(
      static_cast<Backend::ClearBitMask>(Backend::ClearBit::Color) |
      static_cast<Backend::ClearBitMask>(Backend::ClearBit::Depth)
    );
    buildDrawQueue();
    writeDrawQueueToStream(stream);

    stream.writeRenderTargetSet(0);
    stream.writeDisableDepthTest();

    stream.writeClear(static_cast<Backend::ClearBitMask>(Backend::ClearBit::Color));
    writeMerge(stream);
  }

  void WorldRenderer::writeShadowMap(CommandStream &stream) {
    stream.writeRenderTargetSet(RenderTargets::handles.shadow);
    stream.writeClear(static_cast<Backend::ClearBitMask>(Backend::ClearBit::Depth));

    stream.writeProgramSet(Programs::handles[static_cast<size_t>(ProgramName::ShadowStatic)]);
    stream.writeUniformMat4Set(Uniforms::list.shadowStaticViewClipTransform, 1, lightTransforms.viewClip.components);
    stream.writeUniformMat4Set(Uniforms::list.shadowStaticWorldViewTransform, 1, lightTransforms.worldView.components);
    const StaticDrawSet &staticSet = drawSet.staticSet;
    for(uint16_t i=0; staticSet.count>i; i++) {
      const StaticMesh& mesh = StaticMeshes::get(staticSet.meshes[i]);
      stream.writeUniformMat4Set(
        Uniforms::list.shadowStaticModelWorldTransform,
        1,
        staticSet.transforms[i].components
      );
      stream.writeObjectSet(mesh.object);
      stream.writeIndexedDraw(mesh.indexCount, Backend::DataType::UnsignedShort);
    }

    stream.writeProgramSet(Programs::handles[static_cast<size_t>(ProgramName::ShadowBone)]);
    stream.writeUniformMat4Set(Uniforms::list.shadowBoneViewClipTransform, 1, lightTransforms.viewClip.components);
    stream.writeUniformMat4Set(Uniforms::list.shadowBoneWorldViewTransform, 1, lightTransforms.worldView.components);
    const BoneDrawSet &boneSet = drawSet.boneSet;
    for(uint16_t i=0; boneSet.count>i; i++) {
      BoneMesh mesh = boneMeshRegistry.get(boneSet.meshes[i]);

      stream.writeUniformMat4Set(
        Uniforms::list.shadowBoneJointWorldTransform,
        1,
        boneSet.transforms[i].components
      );

      stream.writeUniformMat4Set(
        Uniforms::list.shadowBoneModelJointTransforms,
        8,
        boneSet.poses[i].joints[0].components
      );

      stream.writeObjectSet(mesh.object);
      stream.writeIndexedDraw(mesh.indexCount, Backend::DataType::UnsignedShort);
    }

    stream.writeRenderTargetSet(0);
  }

  void WorldRenderer::calcLightTransforms() {
    // todo: move this (and probably also corner calc) to calcFrustumMetadata() - it is also used in calcFrustum
    float aspectRatio = (800.0/600.0); // todo replace with real aspect ratio
    float nearWidth = tan(Config::perspective.fieldOfView/2)*2*Config::perspective.near;
    float nearHeight = nearWidth/aspectRatio;
    float farWidth = nearWidth*(Config::perspective.far/Config::perspective.near);
    float farHeight = farWidth/aspectRatio;

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
    corners[NearTopLeft] = Quanta::Vector3(-nearWidth*0.5, nearHeight*0.5, Config::perspective.near);
    corners[NearTopRight] = Quanta::Vector3(corners[NearTopLeft][0]*-1, corners[NearTopLeft][1], corners[NearTopLeft][2]);
    corners[NearBottomLeft] = Quanta::Vector3(corners[NearTopLeft][0], corners[NearTopLeft][1]*-1, corners[NearTopLeft][2]);
    corners[NearBottomRight] = Quanta::Vector3(corners[NearBottomLeft][0]*-1, corners[NearBottomLeft][1], corners[NearBottomLeft][2]);
    corners[FarTopLeft] = Quanta::Vector3(farWidth*0.5, farHeight*0.5, Config::perspective.far);
    corners[FarTopRight] = Quanta::Vector3(corners[FarTopLeft][0]*-1, corners[FarTopLeft][1], corners[FarTopLeft][2]);
    corners[FarBottomLeft] = Quanta::Vector3(corners[FarTopLeft][0], corners[FarTopLeft][1]*-1, corners[FarTopLeft][2]);
    corners[FarBottomRight] = Quanta::Vector3(corners[FarBottomLeft][0]*-1, corners[FarBottomLeft][1], corners[FarBottomLeft][2]);
    Quanta::Matrix4 cameraModelWorld = cameraTransform.getMatrix();
    Quanta::Vector3 centroid = Quanta::Vector3::zero();
    for(uint8_t i=0; 8>i; i++) {
      Quanta::Vector4 temp(corners[i][0], corners[i][1], corners[i][2], 1);
      Quanta::Transformer::updateVector4(temp, cameraModelWorld);
      corners[i] = Quanta::Vector3(temp[0], temp[1], temp[2]);
      centroid += corners[i];
    }
    centroid *= 0.125;

    Quanta::Vector3 forward = lightDirection;
    Quanta::Vector3 right = Quanta::Vector3::cross(Quanta::Vector3(0, 1, 0), forward).getNormalized();
    Quanta::Vector3 up = Quanta::Vector3::cross(forward, right).getNormalized();

    Quanta::Matrix4 worldView = Quanta::Matrix4::identity();
    worldView[0] = right[0];
    worldView[4] = right[1];
    worldView[8] = right[2];
    worldView[1] = up[0];
    worldView[5] = up[1];
    worldView[9] = up[2];
    worldView[2] = forward[0];
    worldView[6] = forward[1];
    worldView[10] = forward[2];

    Quanta::Vector3 position = centroid - lightDirection*Config::perspective.far;
    worldView *= Quanta::TransformFactory3D::translation(position*-1);

    lightTransforms.worldView = worldView;

    for(uint8_t i=0; 8>i; i++) {
      Quanta::Vector4 temp(corners[i][0], corners[i][1], corners[i][2], 1);
      Quanta::Transformer::updateVector4(temp, worldView);
      corners[i] = Quanta::Vector3(temp[0], temp[1], temp[2]);
    }

    Quanta::Vector3 mins = corners[0];
    Quanta::Vector3 maxes = corners[0];
    for(uint8_t i=0; 8>i; i++) { // change i=0 to i=1?
      mins[0] = fminf(mins[0], corners[i][0]);
      mins[1] = fminf(mins[1], corners[i][1]);
      mins[2] = fminf(mins[2], corners[i][2]);
      maxes[0] = fmaxf(maxes[0], corners[i][0]);
      maxes[1] = fmaxf(maxes[1], corners[i][1]);
      maxes[2] = fmaxf(maxes[2], corners[i][2]);
    }

    lightTransforms.viewClip = Quanta::ProjectionFactory::ortho(mins[0], maxes[0], mins[1], maxes[1], mins[2]-5.0, maxes[2]);
  }

  void WorldRenderer::writeMerge(CommandStream &stream) {
    stream.writeProgramSet(Programs::handles[static_cast<size_t>(ProgramName::Merge)]);

    Quanta::Matrix4 geometryClipWorldTransform = calcViewClipTransform()*cameraTransform.getInverseMatrix();

    geometryClipWorldTransform.invert();

    stream.writeUniformMat4Set(Uniforms::list.mergeGeometryClipWorldTransform, 1, geometryClipWorldTransform.components);

    Quanta::Matrix4 lightWorldClipTransform = lightTransforms.viewClip*lightTransforms.worldView;
    stream.writeUniformMat4Set(Uniforms::list.mergeLightWorldClipTransform, 1, lightWorldClipTransform.components);

    stream.writeUniformVec3Set(Uniforms::list.mergeLightDirection, 1, lightDirection.components);

    stream.writeTextureSet(
      Uniforms::list.mergeDiffuse,
      Textures::list.geometryDiffuse,
      0
    );
    stream.writeTextureSet(
      Uniforms::list.mergeLambert,
      Textures::list.geometryLambert,
      1
    );
    stream.writeTextureSet(
      Uniforms::list.mergeNormal,
      Textures::list.geometryNormal,
      2
    );
    stream.writeTextureSet(
      Uniforms::list.mergeDepth,
      Textures::list.geometryDepth,
      3
    );
    stream.writeTextureSet(
      Uniforms::list.mergeShadow,
      Textures::list.shadow,
      4
    );

    stream.writeObjectSet(FullscreenQuad::object);
    stream.writeIndexedDraw(6, Backend::DataType::UnsignedByte);
    stream.writeObjectSet(0);
  }

  void WorldRenderer::buildDrawQueue() {
    drawQueue.reset();
    const BoneDrawSet &boneSet = drawSet.boneSet;
    for(uint16_t i=0; boneSet.count>i; i++) {
      BoneMeshDrawCall call;
      BoneMesh mesh = boneMeshRegistry.get(boneSet.meshes[i]);
      call.object = mesh.object;
      call.indexCount = mesh.indexCount;
      call.pose = boneSet.poses[i];
      call.transform = boneSet.transforms[i];
      drawQueue.addBoneMesh(call);
    }
    const StaticDrawSet &staticSet = drawSet.staticSet;
    for(uint16_t i=0; staticSet.count>i; i++) {
      StaticMeshDrawCall call;
      const StaticMesh& mesh = StaticMeshes::get(staticSet.meshes[i]);
      call.object = mesh.object;
      call.indexCount = mesh.indexCount;
      call.transform = staticSet.transforms[i];
      drawQueue.addStaticMesh(call);
    }
    drawQueue.sort();
  }

  void WorldRenderer::writeGlobalUniformUpdate(CommandStream &stream) {
    Backend::BufferHandle globalBuffer = Buffers::handles[static_cast<size_t>(BufferName::Global1)];
    stream.writeBufferSet(Backend::BufferTarget::Uniform, globalBuffer);

    Quanta::Vector3 inverseLightDirection = lightDirection.getNegated();
    Quanta::Matrix4 worldViewTransform = cameraTransform.getInverseMatrix();
    Quanta::Matrix4 viewClipTransform = calcViewClipTransform();

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

  Quanta::Matrix4 WorldRenderer::calcViewClipTransform() const {
    float aspectRatio = static_cast<float>(resolution.width)/(resolution.height);
    Quanta::Matrix4 transform = Quanta::ProjectionFactory::perspective(Config::perspective.fieldOfView, aspectRatio, Config::perspective.near, Config::perspective.far);
    return transform;
  }

  void WorldRenderer::writeDrawQueueToStream(CommandStream &stream) {
    for(uint16_t i=0; drawQueue.getCount()>i; i++) {
      const char *buffer = drawQueue.getBuffer(i);
      DrawCallType type = *reinterpret_cast<const DrawCallType*>(buffer);
      const char *drawCall = buffer+sizeof(type);
      switch(type) {
        case DrawCallType::BoneMesh: {
          const BoneMeshDrawCall *boneMeshDrawCall = reinterpret_cast<const BoneMeshDrawCall*>(drawCall);

          stream.writeProgramSet(Programs::handles[static_cast<size_t>(ProgramName::GeometryBone)]);

          stream.writeUniformMat4Set(
            Uniforms::list.geometryBoneJointWorldTransform,
            1,
            &boneMeshDrawCall->transform.components[0]
          );

          stream.writeUniformMat4Set(
            Uniforms::list.geometryBoneModelJointTransform,
            8,
            &boneMeshDrawCall->pose.joints[0].components[0]
          );

          stream.writeObjectSet(boneMeshDrawCall->object);
          stream.writeIndexedDraw(boneMeshDrawCall->indexCount, Backend::DataType::UnsignedShort);
          break;
        }
        case DrawCallType::StaticMesh: {
          const StaticMeshDrawCall *staticMeshDrawCall = reinterpret_cast<const StaticMeshDrawCall*>(drawCall);
          stream.writeProgramSet(Programs::handles[static_cast<size_t>(ProgramName::GeometryStatic)]);
          stream.writeUniformMat4Set(
            Uniforms::list.geometryStaticModelWorldTransform,
            1,
            &staticMeshDrawCall->transform.components[0]
          );
          stream.writeObjectSet(staticMeshDrawCall->object);
          stream.writeIndexedDraw(staticMeshDrawCall->indexCount, Backend::DataType::UnsignedShort);
          break;
        }
        default:
          fatalError("Unknown draw call type.");
          break;
      }
    }
  }

  void WorldRenderer::buildDrawSet() {
    cullResult.clear();
    Quanta::Frustum frustum = calcFrustum();
    uint16_t counts[Config::cullGroupsCount];
    counts[CullGroupNames::Bone] = BoneMeshInstances::getCount();
    counts[CullGroupNames::Static] = StaticMeshInstances::getCount();
    culler.cull(frustum, cullResult, counts);
    // buildVisibleSet here
    drawSet.clear();

    CullResultRange boneRange = cullResult.getRange(CullGroupNames::Bone);
    for(uint16_t i=boneRange.start; boneRange.end>i; i++) {
      uint16_t index = cullResult.indices[i];
      drawSet.boneSet.add(
        BoneMeshInstances::transforms[index],
        BoneMeshInstances::meshes[index],
        BoneMeshInstances::poses[index]
      );
    }
    CullResultRange staticRange = cullResult.getRange(CullGroupNames::Static);
    for(uint16_t i=staticRange.start; staticRange.end>i; i++) {
      uint16_t index = cullResult.indices[i];
      drawSet.staticSet.add(
        StaticMeshInstances::transforms[index],
        StaticMeshInstances::meshes[index]
      );
    }
  }
}
