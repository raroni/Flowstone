#ifndef WATSON_STATE_COLLECTION_H
#define WATSON_STATE_COLLECTION_H

namespace Watson {
  namespace StateCollection {
    void createList(TypeIndex typeIndex);
    void* getNode(TypeIndex typeIndex, uint16_t instanceIndex, NodeIndex nodeIndex);
    void move(TypeIndex typeIndex, uint16_t sourceIndex, uint16_t destinationIndex);
  }
}

#endif
