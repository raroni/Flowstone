#include "Rendering/Backend/Functions.h"
#include "Rendering/AttributeLocation.h"
#include "Rendering/StaticMeshes.h"

namespace Rendering {
  namespace StaticMeshes {
    namespace {
      struct BackendStaticVertex {
        float px, py, pz;
        float nx, ny, nz;
      };
      StaticMesh list[128];
      uint8_t count = 0;
    }

    static void buildBackendMesh(
      const StaticVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount,
      uint8_t *backendVertexCount, BackendStaticVertex *backendVertices, uint16_t *backendIndices
    ) {
      uint8_t triangleCount = indexCount/3;
      for(uint8_t i=0; triangleCount>i; i++) {
        uint8_t indexOffset = i*3;
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
              v.nx == normal[0] && v.ny == normal[1] && v.nz == normal[2]
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
            index = (*backendVertexCount)++;
          }
          backendIndices[indexOffset+m] = index;
        }
      }
    }

    static Backend::ObjectHandle upload(const BackendStaticVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
      Backend::ObjectHandle object = Backend::createObject();
      Backend::setObject(object);

      Backend::enableAttributeLocation(static_cast<Backend::AttributeLocation>(AttributeLocation::Position));
      Backend::enableAttributeLocation(static_cast<Backend::AttributeLocation>(AttributeLocation::Normal));

      Backend::BufferHandle vertexBuffer = Backend::createBuffer();
      Backend::setBuffer(Backend::BufferTarget::Vertex, vertexBuffer);
      Backend::writeBuffer(Backend::BufferTarget::Vertex, sizeof(BackendStaticVertex)*vertexCount, vertices);

      Backend::BufferHandle indexBuffer = Backend::createBuffer();
      Backend::setBuffer(Backend::BufferTarget::Index, indexBuffer);
      Backend::writeBuffer(Backend::BufferTarget::Index, sizeof(uint16_t)*indexCount, indices);

      Backend::configureAttribute(
        static_cast<Backend::AttributeLocation>(AttributeLocation::Position),
        3,
        Backend::DataType::Float,
        sizeof(BackendStaticVertex),
        0
      );
      Backend::configureAttribute(
        static_cast<Backend::AttributeLocation>(AttributeLocation::Normal),
        3,
        Backend::DataType::Float,
        sizeof(BackendStaticVertex),
        sizeof(float)*3
      );

      Backend::setObject(0);

      return object;
    }

    StaticMeshIndex create(const StaticVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
      uint8_t backendVertexCount = 0;
      BackendStaticVertex backendVertices[indexCount];
      uint16_t backendIndices[indexCount];
      buildBackendMesh(vertices, vertexCount, indices, indexCount, &backendVertexCount, backendVertices, backendIndices);
      StaticMesh &mesh = list[count];
      mesh.object = upload(backendVertices, backendVertexCount, backendIndices, indexCount);;
      mesh.indexCount = indexCount;
      return count++;
    }

    const StaticMesh& get(StaticMeshIndex index) {
      return list[index];
    }
  }
}
