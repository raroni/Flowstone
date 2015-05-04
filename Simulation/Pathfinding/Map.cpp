#include <assert.h>
#include "Fixie/Util.h"
#include "Simulation/Pathfinding/MapNeighbourIterator.h"
#include "Simulation/Pathfinding/Map.h"

namespace Simulation {
  static Fixie::Num diagonalCost = Fixie::Util::sqrt(Fixie::Num(2));
  Map map;

  MapFieldIndex Map::calcFieldIndex(MapFieldCoors coors) const {
    assert(width > coors.x);
    assert(height > coors.y);
    return coors.x + coors.y*width;
  }

  MapFieldCoors Map::calcFieldCoors(MapFieldIndex index) const {
    assert(Config::mapSizeMax > index);
    MapFieldCoors coors;
    coors.x = index % width;
    coors.y = index/width;
    return coors;
  }

  void Map::set(MapFieldIndex fieldIndex, MapFieldType type) {
    types[fieldIndex] = type;
    MapFieldCoors fieldCoors = calcFieldCoors(fieldIndex);

    MapNeighbourIterator iterator = MapNeighbourIterator(getSize(), fieldCoors);
    for(;!iterator.isEmpty(); iterator.next()) {
      recalcDirections(iterator.get());
    }
  }

  void Map::recalcDirections(MapFieldCoors centerCoors) {
    MapFieldIndex index = calcFieldIndex(centerCoors);
    MapDirectionList &list = directionLists[index];
    list.clear();

    MapNeighbourIterator iterator = MapNeighbourIterator(getSize(), centerCoors);
    for(;!iterator.isEmpty(); iterator.next()) {
      MapFieldCoors neighbourCoors = iterator.get();
      if(neighbourCoors.x == centerCoors.x && neighbourCoors.y == centerCoors.y) {
        continue;
      }
      MapFieldIndex neighbourIndex = calcFieldIndex(neighbourCoors);
      MapFieldType neighbourType = types[neighbourIndex];
      if(neighbourType == MapFieldType::Grass) {
        bool isOrthogonal = neighbourCoors.x == centerCoors.x || neighbourCoors.y == centerCoors.y;
        if(isOrthogonal) {
          list.add(neighbourIndex, 1);
        } else {
          MapFieldIndex verticalNeighbour = calcFieldIndex({ centerCoors.x, neighbourCoors.y });
          MapFieldIndex horizontalNeighbour = calcFieldIndex({ neighbourCoors.x, centerCoors.y });
          if(types[verticalNeighbour] == MapFieldType::Grass && types[horizontalNeighbour] == MapFieldType::Grass) {
            list.add(neighbourIndex, diagonalCost);
          }
        }
      }
    }
  }

  const MapDirectionList& Map::getDirections(MapFieldIndex field) const {
    return directionLists[field];
  }

  MapArea Map::getSize() const {
    MapArea size = { width, height };
    return size;
  }

  void Map::reset(uint16_t width, uint16_t height, const MapFieldType *types) {
    assert(width <= Config::mapWidthMax);
    assert(height <= Config::mapHeightMax);
    this->width = width;
    this->height = height;

    uint32_t size = width*height;
    for(MapFieldIndex i=0; i<size; ++i) {
      this->types[i] = types[i];
    }
    for(MapFieldIndex i=0; i<size; ++i) {
      recalcDirections(calcFieldCoors(i));
    }
  }
}
