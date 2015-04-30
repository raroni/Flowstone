#include "Fixie/Util.h"
#include "Simulation/Pathfinding/AStarPriorityQueue.h"
#include "Simulation/Pathfinding/AStarCostMap.h"
#include "Simulation/Pathfinding/AStar.h"

namespace Simulation {
  static AStarPriorityQueue frontier;
  static const uint32_t mapFieldMax = Config::mapWidthMax*Config::mapHeightMax;

  // todo: better name
  static MapFieldIndex cameFrom[mapFieldMax];

  static AStarCostMap costs;

  static void cleanUp() {
    frontier.clear();
    costs.clear();
  }

  static Fixie::Num calcManhatten(MapFieldCoors a, MapFieldCoors b) {
    return abs(a.x-b.x) + abs(a.y-b.y);
  }

  static void buildPath(MapSearchResult &result) {

  }

  void aStar(
    const Map &map,
    MapFieldCoors originCoors,
    MapFieldCoors destinationCoors,
    MapSearchResult &result
  ) {
    result.success = false;
    MapFieldIndex originIndex = map.calcFieldIndex(originCoors);
    MapFieldIndex destinationIndex = map.calcFieldIndex(destinationCoors);
    frontier.insert(originIndex, 0);
    cameFrom[originIndex] = originIndex;
    costs.set(originIndex, 0);

    MapFieldIndex currentIndex;
    while(!frontier.isEmpty()) {
      currentIndex = frontier.pop();

      if(currentIndex == destinationIndex) {
        result.success = true;
        buildPath(result);
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
          // todo: ensure not inserted twice
          frontier.insert(waypointIndex, priority);
          cameFrom[waypointIndex] = currentIndex;
        }
      }
    }

    cleanUp();
  }
}
