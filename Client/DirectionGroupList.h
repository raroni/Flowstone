#ifndef CLIENT_DIRECTION_GROUP_LIST_H
#define CLIENT_DIRECTION_GROUP_LIST_H

namespace Client {
  namespace DirectionGroupList {
    GroupIndex create();
    void addInstance(GroupIndex group, Animation::PoseHandle pose, EntityHandle simEntity);
  }
}

#endif
