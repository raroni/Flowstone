#include <assert.h>
#include <algorithm>
#include "Fixie/Util.h"
#include "Misc/Util.h"
#include "Simulation/Pathfinding/Map.h"

namespace Simulation {
  static Fixie::Num diagonalCost = Fixie::Util::sqrt(Fixie::Num(2));

  MapFieldIndex Map::calcFieldIndex(MapFieldCoors coors) {
    assert(width > coors.x);
    assert(height > coors.y);
    return coors.x + coors.y*width;
  }

  MapFieldCoors Map::calcFieldCoors(MapFieldIndex index) {
    assert(Config::mapSizeMax > index);
    MapFieldCoors coors;
    coors.x = index % width;
    coors.y = index/width;
    return coors;
  }

  void Map::set(MapFieldIndex fieldIndex, MapFieldType type) {
    types[fieldIndex] = type;
    MapFieldCoors fieldCoors = calcFieldCoors(fieldIndex);

    MapFieldCoors upperLeft;
    MapFieldCoors lowerRight;
    // todo: byg en iterator som spytter coors ud?
    calcNeighbourArea(fieldCoors, upperLeft, lowerRight);
    for(uint16_t x=upperLeft.x; x<=lowerRight.x; ++x) {
      for(uint16_t y=upperLeft.y; y<=lowerRight.y; ++y) {
        recalcDirections({ x, y });
      }
    }
  }

  void Map::calcNeighbourArea(MapFieldCoors coors, MapFieldCoors &upperLeftCoors, MapFieldCoors &lowerRightCoors) {
    upperLeftCoors.x = Util::maxInt32(0, static_cast<int32_t>(coors.x)-1);
    upperLeftCoors.y = Util::maxInt32(0, static_cast<int32_t>(coors.y)-1);
    lowerRightCoors.x = Util::minInt32(width-1, static_cast<int32_t>(coors.x)+1);
    lowerRightCoors.y = Util::minInt32(height-1, static_cast<int32_t>(coors.y)+1);
  }

  void Map::recalcDirections(MapFieldCoors coors) {
    MapFieldIndex index = calcFieldIndex(coors);
    MapDirectionList &list = directionLists[index];
    list.clear();

    MapFieldCoors upperLeft;
    MapFieldCoors lowerRight;
    calcNeighbourArea(coors, upperLeft, lowerRight);
    for(uint16_t x=upperLeft.x; x<=lowerRight.x; ++x) {
      for(uint16_t y=upperLeft.y; y<=lowerRight.y; ++y) {
        if(x == coors.x && y == coors.y) {
          continue;
        }
        MapFieldCoors neighbourCoors = { x, y };
        MapFieldIndex neighbourIndex = calcFieldIndex(neighbourCoors);
        MapFieldType neighbourType = types[neighbourIndex];
        if(neighbourType == MapFieldType::Grass) {
          bool isOrthogonal = x == coors.x || y == coors.y;
          if(isOrthogonal) {
            list.add(neighbourIndex, 1);
          } else {
            MapFieldIndex verticalNeighbour = calcFieldIndex({ coors.x, neighbourCoors.y });
            MapFieldIndex horizontalNeighbour = calcFieldIndex({ neighbourCoors.x, coors.y });
            if(types[verticalNeighbour] == MapFieldType::Grass && types[horizontalNeighbour] == MapFieldType::Grass) {
              list.add(neighbourIndex, diagonalCost);
            }
          }
        }
      }
    }
  }

  const MapDirectionList& Map::getDirections(MapFieldIndex field) const {
    return directionLists[field];
  }

  uint32_t Map::getSize() const {
    return width*height;
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
