#include <assert.h>
#include "Misc/HandleList.h"
#include "Client/DirectionInstanceList.h"

namespace Client {
  namespace DirectionInstanceList {
    const static uint16_t max = 256;
    uint16_t indices[max];
    DirectionInstanceHandle handles[max];
    HandleList handleList(max, indices, handles);
    DirectionGroupIndex groupIndices[max];
    Animation::PoseHandle poseHandles[max];
    Database::EntityHandle entityHandles[max];

    DirectionInstanceHandle create(
      DirectionGroupIndex groupIndex,
      Animation::PoseHandle poseHandle,
      Database::EntityHandle entityHandle
    ) {
      uint16_t index;
      DirectionInstanceHandle instanceHandle;
      handleList.create(&index, &instanceHandle);
      groupIndices[index] = groupIndex;
      poseHandles[index] = poseHandle;
      entityHandles[index] = entityHandle;
      return instanceHandle;
    }

    uint16_t getIndexByEntity(Database::EntityHandle handle) {
      for(uint16_t i=0; i<handleList.getCount(); ++i) {
        if(entityHandles[i] == handle) {
          return i;
        }
      }
      assert(false);
    }

    DirectionGroupIndex getGroup(uint16_t index) {
      return groupIndices[index];
    }

    Animation::PoseHandle getPoseHandle(uint16_t index) {
      return poseHandles[index];
    }
  }
}
