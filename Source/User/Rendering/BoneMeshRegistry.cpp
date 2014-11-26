#include "Rendering/Backend/Backend.h"
#include "Rendering/Backend/BoneVertex.h"
#include "Rendering/BoneMeshRegistry.h"

namespace Rendering {
  static void buildBackendMesh(
    const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount,
    uint8_t *backendVertexCount, Backend::BoneVertex *backendVertices, uint16_t *backendIndices
  ) {
    uint8_t triangleCount = indexCount/3;
    for(uint8_t i=0; triangleCount>i; i++) {
      uint8_t indexOffset = i*3;
      BoneVertex triangleVertices[] = {
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
        BoneVertex vertex = triangleVertices[m];
        for(uint8_t n=0; *backendVertexCount>n; n++) {
          Backend::BoneVertex &v = backendVertices[n];
          if(
            v.px == vertex.position[0] && v.py == vertex.position[1] && v.pz == vertex.position[2] &&
            v.nx == normal[0] && v.ny == normal[1] && v.nz == normal[2] &&
            v.jointIndex == vertex.jointIndex
          ) {
            found = true;
            index = n;
            break;
          }
        }
        if(!found) {
          Backend::BoneVertex &v = backendVertices[*backendVertexCount];
          v.px = vertex.position[0];
          v.py = vertex.position[1];
          v.pz = vertex.position[2];
          v.nx = normal[0];
          v.ny = normal[1];
          v.nz = normal[2];
          v.jointIndex = vertex.jointIndex;
          index = (*backendVertexCount)++;
        }
        backendIndices[indexOffset+m] = index;
      }
    }
  }

  BoneMeshIndex BoneMeshRegistry::create(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
    uint8_t backendVertexCount = 0;
    Backend::BoneVertex backendVertices[indexCount];
    uint16_t backendIndices[indexCount];
    buildBackendMesh(vertices, vertexCount, indices, indexCount, &backendVertexCount, backendVertices, backendIndices);
    handles[count] = Backend::createBoneMesh(backendVertices, backendVertexCount, backendIndices, indexCount);
    indexCounts[count] = indexCount;
    return count++;
  }
}
