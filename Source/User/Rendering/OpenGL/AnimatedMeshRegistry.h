#ifndef Rendering_OPENGL_ANIMATED_MESH_REGISTRY_H
#define Rendering_OPENGL_ANIMATED_MESH_REGISTRY_H

#include <stddef.h>
#include <OpenGL/gl3.h>
#include "Rendering/AnimatedVertex.h"
#include "Rendering/AnimatedMeshIndex.h"
#include "Rendering/OpenGL/AnimatedMesh.h"

namespace Rendering {
  namespace OpenGL {
    class AnimatedMeshRegistry {
      struct GLAnimatedVertex {
        GLfloat x;
        GLfloat y;
        GLfloat z;
        GLushort jointIndex;
      };
      const static uint8_t maxCount = 64;
      uint16_t count;
      GLuint vaoHandles[maxCount];
      uint16_t indexCounts[maxCount];
    public:
      GLint positionAttributeHandle;
      GLint jointIndexAttributeHandle;
      AnimatedMeshIndex create(const AnimatedVertex *vertices, const size_t vertexCount, const uint16_t *indices, const size_t indexCount) {
        GLuint vaoHandle;
        glGenVertexArrays(1, &vaoHandle);
        glBindVertexArray(vaoHandle);

        glEnableVertexAttribArray(positionAttributeHandle);
        glEnableVertexAttribArray(jointIndexAttributeHandle);

        GLAnimatedVertex oglData[vertexCount];
        for(int i=0; vertexCount>i; i++) {
          GLAnimatedVertex *oglVertex = &oglData[i];
          const AnimatedVertex *inputData = &vertices[i];
          oglVertex->x = inputData->x;
          oglVertex->y = inputData->y;
          oglVertex->z = inputData->z;
          oglVertex->jointIndex = inputData->jointIndex;
        }
        GLuint vertexBufferHandle;
        glGenBuffers(1, &vertexBufferHandle);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
        glBufferData(GL_ARRAY_BUFFER, sizeof(oglData), oglData, GL_STATIC_DRAW);

        glVertexAttribPointer(positionAttributeHandle, 3, GL_FLOAT, GL_FALSE, sizeof(GLAnimatedVertex), 0);
        glVertexAttribIPointer(jointIndexAttributeHandle, 1, GL_UNSIGNED_SHORT, sizeof(GLAnimatedVertex), reinterpret_cast<const GLvoid*>(sizeof(GLfloat)*3));

        GLushort indexData[indexCount];
        for(int i=0; indexCount>i; i++) {
          indexData[i] = indices[i];
        }
        GLuint indexBufferHandle;
        glGenBuffers(1, &indexBufferHandle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);

        indexCounts[count] = indexCount;
        vaoHandles[count] = vaoHandle;

        return count++;
      }

      AnimatedMesh get(AnimatedMeshIndex index) const {
        AnimatedMesh mesh;
        mesh.vaoHandle = vaoHandles[index];
        mesh.indexCount = indexCounts[index];
        return mesh;
      }
    };
  }
}

#endif
