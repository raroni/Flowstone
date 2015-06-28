#ifndef SIMULATION_A_STAR_H
#define SIMULATION_A_STAR_H

#include "Fixie/Num.h"
#include "Simulation/Pathfinding/Map.h"
#include "Simulation/Pathfinding/MapFieldCoors.h"
#include "Simulation/Pathfinding/MapSearchResult.h"

namespace Simulation {
  void aStar(
    const Map &graph,
    MapFieldCoors origin,
    MapFieldCoors destination,
    Fixie::Num tolerance,
    MapSearchResult &result
  );
}

#endif
