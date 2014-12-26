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
    worldRenderer.initialize();
  }

  void Renderer::setLightDirection(Quanta::Vector3 lightDirection) {
    worldRenderer.lightDirection = lightDirection;
  }

  void Renderer::setAtmosphereColor(Quanta::Vector3 color) {
    worldRenderer.setAtmosphereColor(color);
  }

  BoneMeshInstance Renderer::getBoneMeshInstance(BoneMeshInstanceIndex index) {
    return worldRenderer.getBoneMeshInstance(index);
  }

  void Renderer::updateStaticMeshTransform(StaticMeshInstanceIndex index, const Quanta::Matrix4 &transform) {
    worldRenderer.updateStaticMeshTransform(index, transform);
  }

  BoneMeshIndex Renderer::createBoneMesh(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
    return worldRenderer.createBoneMesh(vertices, vertexCount, indices, indexCount);
  }

  StaticMeshIndex Renderer::createStaticMesh(MeshInfo info, const StaticVertex *vertices, const uint16_t *indices, const Shape *shapes) {
    return worldRenderer.createStaticMesh(info, vertices, indices, shapes);
  }

  StaticMeshInstanceIndex Renderer::createStaticMeshInstance(StaticMeshIndex mesh) {
    return worldRenderer.createStaticMeshInstance(mesh);
  }

  Quanta::Transform& Renderer::getCameraTransform() {
    return worldRenderer.cameraTransform;
  }

  void Renderer::updateResolution(uint16_t width, uint16_t height) {
    worldRenderer.updateResolution(width, height);
  }

  BoneMeshInstanceIndex Renderer::createBoneMeshInstance(BoneMeshIndex meshIndex) {
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
          ProgramSetCommand command = stream.readProgramSet();
          Backend::setProgram(command.program);
          break;
        }
        case CommandType::UniformMat4Set: {
          const float *data;
          UniformMat4SetCommand command = stream.readUniformMat4Set(&data);
          Backend::setUniformMat4(command.uniform, command.count, data);
          break;
        }
        case CommandType::UniformVec3Set: {
          const float *data;
          UniformVec3SetCommand command = stream.readUniformVec3Set(&data);
          Backend::setUniformVec3(command.uniform, command.count, data);
          break;
        }
        case CommandType::ObjectSet: {
          ObjectSetCommand command = stream.readObjectSet();
          Backend::setObject(command.object);
          break;
        }
        case CommandType::Clear: {
          ClearCommand command = stream.readClear();
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
          IndexedDrawCommand command = stream.readIndexedDraw();
          Backend::drawIndexed(command.indexCount, command.dataType);
          break;
        }
        case CommandType::RenderTargetSet: {
          RenderTargetSetCommand command = stream.readRenderTargetSet();
          Backend::setRenderTarget(command.renderTarget);
          break;
        }
        case CommandType::TextureSet: {
          TextureSetCommand command = stream.readTextureSet();
          Backend::setTexture(command.uniform, command.texture, command.unit);
          break;
        }
        case CommandType::BufferSet: {
          BufferSetCommand command = stream.readBufferSet();
          Backend::setBuffer(command.target, command.buffer);
          break;
        }
        case CommandType::ViewportSet: {
          ViewportSetCommand command = stream.readViewportSet();
          Backend::setViewport(command.width, command.height);
          break;
        }
        case CommandType::BufferWrite: {
          const void *data;
          BufferWriteCommand command = stream.readBufferWrite(&data);
          Backend::writeBuffer(command.target, command.size, data);
          break;
        }
        default:
          fatalError("Unknown command type.");
          break;
      }
    }
  }
}
