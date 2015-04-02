#include "Quanta/Math/Vector3.h"
#include "Rendering/Config.h"
#include "SysGFX/SysGFX.h"
#include "Rendering/AttributeLocation.h"
#include "Rendering/MeshHelper.h"
#include "Rendering/StaticMeshes.h"

namespace Rendering {
  namespace StaticMeshes {
    namespace {
      struct BackendStaticVertex {
        float px, py, pz;
        float nx, ny, nz;
        float color[3];
        float selfIllumination;
      };
      StaticMesh list[Config::maxStaticMeshes];
      uint8_t count = 0;
    }

    static void buildBackendMesh(
      MeshInfo info, const StaticVertex *vertices, const uint16_t *indices, const Shape *shapes,
      uint8_t *backendVertexCount, BackendStaticVertex *backendVertices, uint16_t *backendIndices
    ) {
      const Shape *shape;
      for(uint8_t i=0; info.shapeCount>i; i++) {
        shape = &shapes[i];
        Quanta::Vector3 color = shape->color;
        float selfIllumination = shape->selfIllumination;
        for(uint8_t n=0; shape->count>n; n++) {
          uint8_t indexOffset = (shape->offset+n)*3;
          StaticVertex triangleVertices[] = {
            vertices[indices[indexOffset]],
            vertices[indices[indexOffset+1]],
            vertices[indices[indexOffset+2]]
          };

          Quanta::Vector3 ab = triangleVertices[1].position-triangleVertices[0].position;
          Quanta::Vector3 ac = triangleVertices[2].position-triangleVertices[0].position;
          Quanta::Vector3 normal = Quanta::Vector3::cross(ac, ab).getNormalized();

          for(uint8_t m=0; 3>m; m++) {
            uint16_t index;
            bool found = false;
            StaticVertex vertex = triangleVertices[m];
            for(uint8_t n=0; *backendVertexCount>n; n++) {
              BackendStaticVertex &v = backendVertices[n];
              if(
                v.px == vertex.position[0] && v.py == vertex.position[1] && v.pz == vertex.position[2] &&
                v.nx == normal[0] && v.ny == normal[1] && v.nz == normal[2] &&
                v.color[0] == color[0] && v.color[1] == color[1] && v.color[2] == color[2] &&
                v.selfIllumination == selfIllumination
              ) {
                found = true;
                index = n;
                break;
              }
            }
            if(!found) {
              BackendStaticVertex &v = backendVertices[*backendVertexCount];
              v.px = vertex.position[0];
              v.py = vertex.position[1];
              v.pz = vertex.position[2];
              v.nx = normal[0];
              v.ny = normal[1];
              v.nz = normal[2];
              v.color[0] = color[0];
              v.color[1] = color[1];
              v.color[2] = color[2];
              v.selfIllumination = selfIllumination;
              index = (*backendVertexCount)++;
            }
            backendIndices[indexOffset+m] = index;
          }
        }
      }
    }

    static SysGFX::ObjectHandle upload(const BackendStaticVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
      SysGFX::ObjectHandle object = SysGFX::createObject();
      SysGFX::setObject(object);

      SysGFX::enableAttributeLocation(static_cast<SysGFX::AttributeLocation>(AttributeLocation::Position));
      SysGFX::enableAttributeLocation(static_cast<SysGFX::AttributeLocation>(AttributeLocation::Normal));
      SysGFX::enableAttributeLocation(static_cast<SysGFX::AttributeLocation>(AttributeLocation::Color));
      SysGFX::enableAttributeLocation(static_cast<SysGFX::AttributeLocation>(AttributeLocation::SelfIllumination));

      SysGFX::BufferHandle vertexBuffer = SysGFX::createBuffer();
      SysGFX::setBuffer(SysGFX::BufferTarget::Vertex, vertexBuffer);
      SysGFX::writeBuffer(SysGFX::BufferTarget::Vertex, sizeof(BackendStaticVertex)*vertexCount, vertices);

      SysGFX::BufferHandle indexBuffer = SysGFX::createBuffer();
      SysGFX::setBuffer(SysGFX::BufferTarget::Index, indexBuffer);
      SysGFX::writeBuffer(SysGFX::BufferTarget::Index, sizeof(uint16_t)*indexCount, indices);

      SysGFX::configureAttribute(
        static_cast<SysGFX::AttributeLocation>(AttributeLocation::Position),
        3,
        SysGFX::DataType::Float,
        sizeof(BackendStaticVertex),
        0
      );
      SysGFX::configureAttribute(
        static_cast<SysGFX::AttributeLocation>(AttributeLocation::Normal),
        3,
        SysGFX::DataType::Float,
        sizeof(BackendStaticVertex),
        sizeof(float)*3
      );
      SysGFX::configureAttribute(
        static_cast<SysGFX::AttributeLocation>(AttributeLocation::Color),
        3,
        SysGFX::DataType::Float,
        sizeof(BackendStaticVertex),
        sizeof(float)*3*2
      );
      SysGFX::configureAttribute(
        static_cast<SysGFX::AttributeLocation>(AttributeLocation::SelfIllumination),
        1,
        SysGFX::DataType::Float,
        sizeof(BackendStaticVertex),
        sizeof(float)*3*3
      );

      SysGFX::setObject(0);

      return object;
    }

    static float calcBoundingRadius(const StaticVertex *vertices, uint16_t count) {
      Quanta::Vector3 positions[count];
      for(uint16_t i=0; count>i; i++) {
        positions[i] = vertices[i].position;
      }
      return MeshHelper::calcBoundingRadius(positions, count);
    }

    StaticMeshIndex create(MeshInfo info, const StaticVertex *vertices, const uint16_t *indices, const Shape *shapes) {
      uint8_t backendVertexCount = 0;
      BackendStaticVertex backendVertices[info.indexCount];
      uint16_t backendIndices[info.indexCount];
      buildBackendMesh(info, vertices, indices, shapes, &backendVertexCount, backendVertices, backendIndices);
      StaticMesh &mesh = list[count];
      mesh.object = upload(backendVertices, backendVertexCount, backendIndices, info.indexCount);;
      mesh.indexCount = info.indexCount;
      mesh.boundingRadius = calcBoundingRadius(vertices, info.vertexCount);
      return count++;
    }

    const StaticMesh& get(StaticMeshIndex index) {
      return list[index];
    }
  }
}
