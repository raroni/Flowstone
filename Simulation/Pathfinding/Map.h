#ifndef SIMULATION_MAP_H
#define SIMULATION_MAP_H

#include "Simulation/Config.h"
#include "Simulation/Pathfinding/MapFieldType.h"
#include "Simulation/Pathfinding/MapDirectionList.h"
#include "Simulation/Pathfinding/MapFieldCoors.h"
#include "Simulation/Pathfinding/MapArea.h"
#include "Simulation/Pathfinding/MapFieldIndex.h"

namespace Simulation {
  class Map {
  public:
    void set(MapFieldIndex field, MapFieldType type);
    const MapDirectionList& getDirections(MapFieldIndex field) const;
    void reset(uint16_t width, uint16_t height, const MapFieldType *types);
    MapFieldIndex calcFieldIndex(MapFieldCoors coors) const;
    MapFieldCoors calcFieldCoors(MapFieldIndex) const;
    MapArea getSize() const;
  private:
    void recalcDirections(MapFieldCoors field);
    uint16_t width = 0;
    uint16_t height = 0;
    MapFieldType types[Config::mapSizeMax];
    MapDirectionList directionLists[Config::mapSizeMax];
  };

  extern Map map;
}

#endif
