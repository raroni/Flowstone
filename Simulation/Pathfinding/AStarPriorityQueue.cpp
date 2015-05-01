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

  void AStarPriorityQueue::bubbleUp(uint32_t currentIndex) {
    const Node originalNode = nodes[currentIndex];
    while(1) {
      if(currentIndex == 0) {
        break;
      }

      const uint32_t parentIndex = calcParentIndex(currentIndex);
      if(originalNode.priority >= nodes[parentIndex].priority) {
        break;
      }

      saveNode(currentIndex, nodes[parentIndex]);
      currentIndex = parentIndex;
    }
    saveNode(currentIndex, originalNode);
  }

  void AStarPriorityQueue::saveNode(uint32_t index, Node node) {
    nodes[index] = node;
    indices[node.field] = index;
  }

  void AStarPriorityQueue::insert(MapFieldIndex field, Fixie::Num priority) {
    assert(count != max);
    uint32_t index = count++;
    saveNode(index, { field, priority });
    bubbleUp(index);
  }

  void AStarPriorityQueue::update(MapFieldIndex field, Fixie::Num newPriority) {
    uint32_t index = indices[field];
    Fixie::Num oldPriority = nodes[index].priority;
    saveNode(index, { field, newPriority });
    if(oldPriority < newPriority) {
      bubbleDown(index);
    } else {
      bubbleUp(index);
    }
  }

  bool AStarPriorityQueue::isEmpty() const {
    return count == 0;
  }

  void AStarPriorityQueue::clear() {
    count = 0;
  }

  void AStarPriorityQueue::bubbleDown(uint32_t currentIndex) {
    Node originalNode = nodes[currentIndex];
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
        saveNode(currentIndex, nodes[smallest]);
        currentIndex = smallest;
      } else {
        break;
      }
    }
    saveNode(currentIndex, originalNode);
  }

  MapFieldIndex AStarPriorityQueue::pop() {
    assert(count != 0);
    MapFieldIndex result = nodes[0].field;
    nodes[0] = nodes[--count];
    bubbleDown(0);
    return result;
  }
}
