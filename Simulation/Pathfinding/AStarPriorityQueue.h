#ifndef SIMULATION_A_STAR_PRIORITY_QUEUE_H
#define SIMULATION_A_STAR_PRIORITY_QUEUE_H

#include "Fixie/Num.h"
#include "Simulation/Config.h"
#include "Simulation/Pathfinding/MapFieldIndex.h"

namespace Simulation {
  class AStarPriorityQueue {
  public:
    void insert(MapFieldIndex field, Fixie::Num priority);
    MapFieldIndex pop();
    bool isEmpty() const;
    void clear();
  private:
    static const uint32_t max = Config::mapSizeMax;
    struct Node {
      MapFieldIndex field;
      Fixie::Num priority;
    };
    void swap(uint32_t indexA, uint32_t indexB);
    Node nodes[max];
    uint32_t count = 0;
  };
}

#endif
