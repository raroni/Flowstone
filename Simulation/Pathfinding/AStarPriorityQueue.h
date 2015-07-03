#ifndef SIMULATION_A_STAR_PRIORITY_QUEUE_H
#define SIMULATION_A_STAR_PRIORITY_QUEUE_H

#include "Fixie/Num.h"
#include "Simulation/Config.h"
#include "Simulation/Pathfinding/MapFieldIndex.h"

namespace Simulation {
  class AStarPriorityQueue {
  public:
    void insert(MapFieldIndex field, Fixie::Num priority);
    void update(MapFieldIndex field, Fixie::Num priority);
    MapFieldIndex pop();
    bool isEmpty() const;
    void clear();
  private:
    struct Node {
      MapFieldIndex field;
      Fixie::Num priority;
    };
    void bubbleDown(uint32_t index);
    void bubbleUp(uint32_t index);
    void saveNode(uint32_t index, Node node);
    static const uint32_t max = Config::mapSizeMax;
    Node nodes[max];
    uint32_t indices[max];
    uint32_t count = 0;
  };
}

#endif
