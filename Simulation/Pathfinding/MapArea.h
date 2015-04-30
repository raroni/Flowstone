#ifndef SIMULATION_MAP_AREA_H
#define SIMULATION_MAP_AREA_H

namespace Simulation {
  struct MapArea {
    uint16_t width;
    uint16_t height;
    uint32_t calcFieldCount() const {
      return width*height;
    }
  };
}

#endif
