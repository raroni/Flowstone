#ifndef WATSON_BOARD_COLLECTION_H
#define WATSON_BOARD_COLLECTION_H

#include "Watson/Board.h"

namespace Watson {
  namespace BoardCollection {
    void createList(TypeIndex typeIndex);
    Board* get(TypeIndex typeIndex, uint16_t instanceIndex);
    void move(TypeIndex typeIndex, uint16_t sourceIndex, uint16_t destinationIndex);
  }
}

#endif
