#include "Simulation/Pathfinding/AStarPriorityQueue.h"

namespace Simulation {
  static uint32_t calcParentIndex(uint32_t index) {
    return floor((index-1)/2);
  }

  static uint32_t calcLeftChildIndex(uint32_t index) {
    return index*2+1;
  }

  static uint32_t calcRightChildIndex(uint32_t index) {
    return index*2+2;
  }

  void AStarPriorityQueue::insert(MapNodeIndex node, Fixie::Num priority) {
    assert(count != max);

    uint32_t currentIndex = count++;
    while(1) {
      if(currentIndex == 0) {
        break;
      }

      const uint32_t parentIndex = calcParentIndex(currentIndex);
      if(priority >= nodes[parentIndex].priority) {
        break;
      }

      nodes[currentIndex] = nodes[parentIndex];
      currentIndex = parentIndex;
    }
    nodes[currentIndex].mapNodeIndex = node;
    nodes[currentIndex].priority = priority;
  }

  void AStarPriorityQueue::swap(uint32_t indexA, uint32_t indexB) {
    Node temp = nodes[indexA];
    nodes[indexA] = nodes[indexB];
    nodes[indexB] = temp;
  }

  bool AStarPriorityQueue::isEmpty() const {
    return count == 0;
  }

  MapNodeIndex AStarPriorityQueue::pop() {
    MapNodeIndex result = nodes[0].mapNodeIndex;
    nodes[0] = nodes[--count];

    uint32_t currentIndex = 0;
    while(1) {
      uint32_t smallest = currentIndex;
      uint32_t leftChildIndex = calcLeftChildIndex(currentIndex);
      if(leftChildIndex < count && nodes[leftChildIndex].priority < nodes[smallest].priority) {
        smallest = leftChildIndex;
      }
      uint32_t rightChildIndex = calcRightChildIndex(currentIndex);
      if(rightChildIndex < count && nodes[rightChildIndex].priority < nodes[smallest].priority) {
        smallest = rightChildIndex;
      }
      if(smallest != currentIndex) {
        swap(smallest, currentIndex);
        currentIndex = smallest;
      } else {
        break;
      }
    }
    return result;
  }
}
