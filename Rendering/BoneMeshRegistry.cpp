#include "SysGFX/SysGFX.h"
#include "Rendering/AttributeLocation.h"
#include "Rendering/MeshHelper.h"
#include "Rendering/BoneMeshRegistry.h"

namespace Rendering {
  namespace {
    struct BackendBoneVertex {
      float px, py, pz;
      float nx, ny, nz;
      uint8_t jointIndex;
    };
  }

  static void buildBackendMesh(
    const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount,
    uint8_t *backendVertexCount, BackendBoneVertex *backendVertices, uint16_t *backendIndices
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
          BackendBoneVertex &v = backendVertices[n];
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
          BackendBoneVertex &v = backendVertices[*backendVertexCount];
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

  static SysGFX::ObjectHandle upload(const BackendBoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
    SysGFX::ObjectHandle object = SysGFX::createObject();
    SysGFX::setObject(object);

    SysGFX::enableAttributeLocation(static_cast<SysGFX::AttributeLocation>(AttributeLocation::Position));
    SysGFX::enableAttributeLocation(static_cast<SysGFX::AttributeLocation>(AttributeLocation::Normal));
    SysGFX::enableAttributeLocation(static_cast<SysGFX::AttributeLocation>(AttributeLocation::JointIndex));

    SysGFX::BufferHandle vertexBuffer = SysGFX::createBuffer();
    SysGFX::setBuffer(SysGFX::BufferTarget::Vertex, vertexBuffer);
    SysGFX::writeBuffer(SysGFX::BufferTarget::Vertex, sizeof(BackendBoneVertex)*vertexCount, vertices);

    SysGFX::BufferHandle indexBuffer = SysGFX::createBuffer();
    SysGFX::setBuffer(SysGFX::BufferTarget::Index, indexBuffer);
    SysGFX::writeBuffer(SysGFX::BufferTarget::Index, sizeof(uint16_t)*indexCount, indices);

    SysGFX::configureAttribute(
      static_cast<SysGFX::AttributeLocation>(AttributeLocation::Position),
      3,
      SysGFX::DataType::Float,
      sizeof(BackendBoneVertex),
      0
    );
    SysGFX::configureAttribute(
      static_cast<SysGFX::AttributeLocation>(AttributeLocation::Normal),
      3,
      SysGFX::DataType::Float,
      sizeof(BackendBoneVertex),
      sizeof(float)*3
    );
    SysGFX::configureAttribute(
      static_cast<SysGFX::AttributeLocation>(AttributeLocation::JointIndex),
      1,
      SysGFX::DataType::UnsignedByte,
      sizeof(BackendBoneVertex),
      sizeof(float)*6
    );

    SysGFX::setObject(0);

    return object;
  }

  static float calcBoundingRadius(const BoneVertex *vertices, uint16_t count) {
    Quanta::Vector3 positions[count];
    for(uint16_t i=0; count>i; i++) {
      positions[i] = vertices[i].position;
    }
    return MeshHelper::calcBoundingRadius(positions, count);
  }

  BoneMeshIndex BoneMeshRegistry::create(const BoneVertex *vertices, const uint16_t vertexCount, const uint16_t *indices, const uint16_t indexCount) {
    uint8_t backendVertexCount = 0;
    BackendBoneVertex backendVertices[indexCount];
    uint16_t backendIndices[indexCount];
    buildBackendMesh(vertices, vertexCount, indices, indexCount, &backendVertexCount, backendVertices, backendIndices);
    handles[count] = upload(backendVertices, backendVertexCount, backendIndices, indexCount);
    boundingRadii[count] = calcBoundingRadius(vertices, vertexCount);
    indexCounts[count] = indexCount;
    return count++;
  }

  BoneMesh BoneMeshRegistry::get(BoneMeshIndex index) const {
    BoneMesh mesh;
    mesh.object = handles[index];
    mesh.indexCount = indexCounts[index];
    mesh.boundingRadius = boundingRadii[index];
    return mesh;
  }
}
