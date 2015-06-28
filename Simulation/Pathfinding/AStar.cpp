#include <assert.h>
#include "Fixie/Util.h"
#include "Simulation/Pathfinding/AStarPriorityQueue.h"
#include "Simulation/Pathfinding/AStarCostMap.h"
#include "Simulation/Pathfinding/AStar.h"

namespace Simulation {
  static AStarPriorityQueue frontier;
  static const uint32_t mapFieldMax = Config::mapWidthMax*Config::mapHeightMax;
  static MapFieldIndex pathParents[mapFieldMax];
  static AStarCostMap costs;
  static MapFieldIndex buildCache[Config::mapSizeMax];

  static void cleanUp() {
    frontier.clear();
    costs.clear();
  }

  static Fixie::Num calcManhatten(MapFieldCoors a, MapFieldCoors b) {
    return abs(a.x-b.x) + abs(a.y-b.y);
  }

  static void buildPath(
    MapSearchResult &result,
    const Map &map,
    MapFieldIndex originIndex,
    MapFieldIndex destinationIndex
  ) {
    MapFieldIndex currentIndex = destinationIndex;
    uint32_t count = 0;
    for(count=0; originIndex != currentIndex; ++count) {
      assert(count != Config::mapSizeMax);
      buildCache[count] = currentIndex;
      currentIndex = pathParents[currentIndex];
    }

    for(uint16_t i=0; i<count; ++i) {
      result.add(map.calcFieldCoors(buildCache[count-1-i]));
    }
  }

  void aStar(
    const Map &map,
    MapFieldCoors originCoors,
    MapFieldCoors destinationCoors,
    Fixie::Num tolerance,
    MapSearchResult &result
  ) {
    result.success = false;
    MapFieldIndex originIndex = map.calcFieldIndex(originCoors);
    MapFieldIndex destinationIndex = map.calcFieldIndex(destinationCoors);
    frontier.insert(originIndex, 0);
    pathParents[originIndex] = originIndex;
    costs.set(originIndex, 0);

    MapFieldCoors currentCoors;
    MapFieldIndex currentIndex;
    while(!frontier.isEmpty()) {
      currentIndex = frontier.pop();
      currentCoors = map.calcFieldCoors(currentIndex);
      if(calcManhatten(currentCoors, destinationCoors) <= tolerance) {
        result.success = true;
        if(destinationIndex != currentIndex) {
          pathParents[destinationIndex] = currentIndex;
        }
        buildPath(result, map, originIndex, destinationIndex);
        break;
      }

      const MapDirectionList &directions = map.getDirections(currentIndex);
      for(uint8_t i=0; i<directions.count; ++i) {
        MapFieldIndex waypointIndex = directions.destinations[i];
        Fixie::Num currentCost;
        costs.get(currentIndex, currentCost);
        Fixie::Num newCost = currentCost + directions.costs[i];
        Fixie::Num existingCost;
        bool found = costs.get(waypointIndex, existingCost);
        if(!found || newCost < existingCost) {
          costs.set(waypointIndex, newCost);
          MapFieldCoors waypointCoors = map.calcFieldCoors(waypointIndex);
          Fixie::Num priority = newCost + calcManhatten(waypointCoors, destinationCoors);
          pathParents[waypointIndex] = currentIndex;
          if(found) {
            frontier.update(waypointIndex, priority);
          } else {
            frontier.insert(waypointIndex, priority);
          }
        }
      }
    }

    cleanUp();
  }
}
