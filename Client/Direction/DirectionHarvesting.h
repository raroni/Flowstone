#ifndef CLIENT_DIRECTION_CHOPPING_H
#define CLIENT_DIRECTION_CHOPPING_H

#include "Simulation/Event/HarvestWorkStartEvent.h"
#include "Client/Direction/DirectionHarvestingConfig.h"
#include "Client/Direction/DirectionGroupIndex.h"

namespace Client {
  namespace DirectionHarvesting {
    void processStartEvent(const Simulation::HarvestWorkStartEvent *event);
    void configureGroup(DirectionGroupIndex group, DirectionHarvestingConfig config);
  }
}

#endif
