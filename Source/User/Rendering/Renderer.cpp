#include "Core/Error.h"
#include "Rendering/Textures.h"
#include "Rendering/Renderer.h"
#include "Rendering/Programs.h"
#include "Rendering/Backend/Functions.h"
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
    Backend::setClearColor(0, 0, 1);
    Backend::enableFaceCulling();
    Backend::disableDepthTest();
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
          Backend::setProgram(command.program);
          break;
        }
        case CommandType::UniformMat4Set: {
          const float *data;
          const UniformMat4SetCommand &command = stream.readUniformMat4Set(&data);
          Backend::setUniformMat4(command.uniform, command.count, data);
          break;
        }
        case CommandType::UniformFloatSet: {
          const float *data;
          const UniformFloatSetCommand &command = stream.readUniformFloatSet(&data);
          Backend::setUniformFloat(command.uniform, command.count, data);
          break;
        }
        case CommandType::UniformVec2Set: {
          const float *data;
          const UniformVec2SetCommand &command = stream.readUniformVec2Set(&data);
          Backend::setUniformVec2(command.uniform, command.count, data);
          break;
        }
        case CommandType::UniformVec3Set: {
          const float *data;
          const UniformVec3SetCommand &command = stream.readUniformVec3Set(&data);
          Backend::setUniformVec3(command.uniform, command.count, data);
          break;
        }
        case CommandType::ObjectSet: {
          const ObjectSetCommand &command = stream.readObjectSet();
          Backend::setObject(command.object);
          break;
        }
        case CommandType::Clear: {
          const ClearCommand &command = stream.readClear();
          Backend::clear(command.mask);
          break;
        }
        case CommandType::EnableDepthTest: {
          Backend::enableDepthTest();
          break;
        }
        case CommandType::DisableDepthTest: {
          Backend::disableDepthTest();
          break;
        }
        case CommandType::IndexedDraw: {
          const IndexedDrawCommand &command = stream.readIndexedDraw();
          Backend::drawIndexed(command.indexCount, command.dataType);
          break;
        }
        case CommandType::RenderTargetSet: {
          const RenderTargetSetCommand &command = stream.readRenderTargetSet();
          Backend::setRenderTarget(command.renderTarget);
          break;
        }
        case CommandType::TexturePairSet: {
          const TexturePairSetCommand &command = stream.readTexturePairSet();
          Backend::setTextureUnit(command.unit);
          Backend::setTexture(command.handle);
          break;
        }
        case CommandType::TextureSet: {
          const TextureSetCommand &command = stream.readTextureSet();
          Backend::setTexture(command.handle);
          break;
        }
        case CommandType::BlendFunctionSet: {
          const BlendFunctionSetCommand &command = stream.readBlendFunctionSet();
          Backend::setBlendFunction(command.sourceFactor, command.destinationFactor);
          break;
        }
        case CommandType::TextureUnitSet: {
          const TextureUnitSetCommand &command = stream.readTextureUnitSet();
          Backend::setTextureUnit(command.unit);
          break;
        }
        case CommandType::BufferSet: {
          const BufferSetCommand &command = stream.readBufferSet();
          Backend::setBuffer(command.target, command.buffer);
          break;
        }
        case CommandType::ViewportSet: {
          const ViewportSetCommand &command = stream.readViewportSet();
          Backend::setViewport(command.width, command.height);
          break;
        }
        case CommandType::BufferWrite: {
          const void *data;
          const BufferWriteCommand &command = stream.readBufferWrite(&data);
          Backend::writeBuffer(command.target, command.size, data);
          break;
        }
        case CommandType::EnableBlending: {
          Backend::enableBlending();
          break;
        }
        case CommandType::DisableBlending: {
          Backend::disableBlending();
          break;
        }
        case CommandType::CullFaceSet: {
          const CullFaceSetCommand &command = stream.readCullFaceSet();
          Backend::setCullFace(command.face);
          break;
        }
        default:
          fatalError("Unknown command type.");
          break;
      }
    }
  }
}
