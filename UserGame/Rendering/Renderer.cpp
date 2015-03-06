#include "Common/Error.h"
#include "Rendering/Textures.h"
#include "Rendering/Renderer.h"
#include "Rendering/Programs.h"
#include "SysGFX/SysGFX.h"
#include "Rendering/Buffers.h"
#include "Rendering/FullscreenQuad.h"
#include "Rendering/RenderTargets.h"
#include "Rendering/Uniforms.h"
#include "Rendering/CommandType.h"

namespace Rendering {
  void Renderer::initialize() {
    Textures::initialize();
    RenderTargets::initialize();
    Buffers::initialize();
    Programs::initialize();
    Uniforms::initialize();
    FullscreenQuad::initialize();
    SysGFX::setClearColor(0, 0, 1);
    SysGFX::enableFaceCulling();
    SysGFX::disableDepthTest();
    worldRenderer.initialize();
  }

  void Renderer::setPrimaryLightDirection(Quanta::Vector3 lightDirection) {
    worldRenderer.primaryLightDirection = lightDirection;
  }

  void Renderer::setSecondaryLightDirection(Quanta::Vector3 lightDirection) {
    worldRenderer.secondaryLightDirection = lightDirection;
  }

  void Renderer::setPrimaryLightColor(Quanta::Vector3 color) {
    worldRenderer.setPrimaryLightColor(color);
  }

  BoneMeshInstance Renderer::getBoneMeshInstance(BoneMeshInstanceHandle handle) {
    return worldRenderer.getBoneMeshInstance(handle);
  }

  PointLightHandle Renderer::createPointLight() {
    return worldRenderer.createPointLight();
  }

  void Renderer::updatePointLightPosition(PointLightHandle handle, const Quanta::Vector3 &position) {
    worldRenderer.updatePointLightPosition(handle, position);
  }

  void Renderer::updateStaticMeshTransform(StaticMeshInstanceHandle handle, const Quanta::Matrix4 &transform) {
    worldRenderer.updateStaticMeshTransform(handle, transform);
  }

  BoneMeshIndex Renderer::createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
    return worldRenderer.createBoneMesh(vertices, vertexCount, indices, indexCount);
  }

  StaticMeshIndex Renderer::createStaticMesh(MeshInfo info, const StaticVertex *vertices, const uint16_t *indices, const Shape *shapes) {
    return worldRenderer.createStaticMesh(info, vertices, indices, shapes);
  }

  StaticMeshInstanceHandle Renderer::createStaticMeshInstance(StaticMeshIndex mesh) {
    return worldRenderer.createStaticMeshInstance(mesh);
  }

  Quanta::Transform& Renderer::getCameraTransform() {
    return worldRenderer.cameraTransform;
  }

  void Renderer::updateResolution(Resolution resolution) {
    worldRenderer.updateResolution(resolution);
    Textures::handleResolutionChange(resolution);
    RenderTargets::handleResolutionChange();
  }

  BoneMeshInstanceHandle Renderer::createBoneMeshInstance(BoneMeshIndex meshIndex) {
    return worldRenderer.createBoneMeshInstance(meshIndex);
  }

  void Renderer::draw() {
    worldRenderer.writeCommands(stream);
    // uiRenderer.writeCommands(stream);
    stream.rewind();
    dispatch();
    stream.reset();
  }

  void Renderer::dispatch() {
    for(uint16_t i=0; stream.getCount()>i; i++) {
      CommandType type = stream.readType();
      switch(type) {
        case CommandType::ProgramSet: {
          const ProgramSetCommand &command = stream.readProgramSet();
          SysGFX::setProgram(command.program);
          break;
        }
        case CommandType::UniformMat4Set: {
          const float *data;
          const UniformMat4SetCommand &command = stream.readUniformMat4Set(&data);
          SysGFX::setUniformMat4(command.uniform, command.count, data);
          break;
        }
        case CommandType::UniformFloatSet: {
          const float *data;
          const UniformFloatSetCommand &command = stream.readUniformFloatSet(&data);
          SysGFX::setUniformFloat(command.uniform, command.count, data);
          break;
        }
        case CommandType::UniformVec2Set: {
          const float *data;
          const UniformVec2SetCommand &command = stream.readUniformVec2Set(&data);
          SysGFX::setUniformVec2(command.uniform, command.count, data);
          break;
        }
        case CommandType::UniformVec3Set: {
          const float *data;
          const UniformVec3SetCommand &command = stream.readUniformVec3Set(&data);
          SysGFX::setUniformVec3(command.uniform, command.count, data);
          break;
        }
        case CommandType::ObjectSet: {
          const ObjectSetCommand &command = stream.readObjectSet();
          SysGFX::setObject(command.object);
          break;
        }
        case CommandType::Clear: {
          const ClearCommand &command = stream.readClear();
          SysGFX::clear(command.mask);
          break;
        }
        case CommandType::EnableDepthTest: {
          SysGFX::enableDepthTest();
          break;
        }
        case CommandType::DisableDepthTest: {
          SysGFX::disableDepthTest();
          break;
        }
        case CommandType::IndexedDraw: {
          const IndexedDrawCommand &command = stream.readIndexedDraw();
          SysGFX::drawIndexed(command.indexCount, command.dataType);
          break;
        }
        case CommandType::RenderTargetSet: {
          const RenderTargetSetCommand &command = stream.readRenderTargetSet();
          SysGFX::setRenderTarget(command.renderTarget);
          break;
        }
        case CommandType::TexturePairSet: {
          const TexturePairSetCommand &command = stream.readTexturePairSet();
          SysGFX::setTextureUnit(command.unit);
          SysGFX::setTexture(command.handle);
          break;
        }
        case CommandType::TextureSet: {
          const TextureSetCommand &command = stream.readTextureSet();
          SysGFX::setTexture(command.handle);
          break;
        }
        case CommandType::BlendFunctionSet: {
          const BlendFunctionSetCommand &command = stream.readBlendFunctionSet();
          SysGFX::setBlendFunction(command.sourceFactor, command.destinationFactor);
          break;
        }
        case CommandType::TextureUnitSet: {
          const TextureUnitSetCommand &command = stream.readTextureUnitSet();
          SysGFX::setTextureUnit(command.unit);
          break;
        }
        case CommandType::BufferSet: {
          const BufferSetCommand &command = stream.readBufferSet();
          SysGFX::setBuffer(command.target, command.buffer);
          break;
        }
        case CommandType::ViewportSet: {
          const ViewportSetCommand &command = stream.readViewportSet();
          SysGFX::setViewport(command.width, command.height);
          break;
        }
        case CommandType::BufferWrite: {
          const void *data;
          const BufferWriteCommand &command = stream.readBufferWrite(&data);
          SysGFX::writeBuffer(command.target, command.size, data);
          break;
        }
        case CommandType::EnableBlending: {
          SysGFX::enableBlending();
          break;
        }
        case CommandType::DisableBlending: {
          SysGFX::disableBlending();
          break;
        }
        case CommandType::CullFaceSet: {
          const CullFaceSetCommand &command = stream.readCullFaceSet();
          SysGFX::setCullFace(command.face);
          break;
        }
        default:
          fatalError("Unknown command type.");
          break;
      }
    }
  }
}
