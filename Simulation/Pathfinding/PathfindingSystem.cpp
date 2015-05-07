#include "SysTime/SysTime.h"
#include "Fixie/Util.h"
#include "Misc/HandleList.h"
#include "Physics/BodyHandle.h"
#include "Physics/Body.h"
#include "Simulation/PhysicsHack.h"
#include "Simulation/Config.h"
#include "Simulation/Pathfinding/Path.h"
#include "Simulation/Steering/Steering.h"
#include "Simulation/Steering/SteeringSystem.h"
#include "Simulation/Pathfinding/Map.h"
#include "Simulation/Pathfinding/AStar.h"
#include "Simulation/Pathfinding/PathfindingSystem.h"

namespace Simulation {
  namespace PathfindingSystem {
    static const uint16_t max = Config::pathfinderMax;
    const SysTime::MSecond16 repathInterval = 5000;
    Fixie::Vector2 targets[max];
    SteeringHandle steeringHandles[max];
    Physics::BodyHandle bodyHandles[max];
    SysTime::MSecond16S remainingRepathTimes[max];
    Path paths[max];
    uint16_t indices[max];
    uint16_t handles[max];
    HandleList handleList(max, indices, handles);
    MapSearchResult mapSearchResult;

    PathfinderHandle create(const Physics::BodyHandle bodyHandle, const SteeringHandle steeringHandle, const Fixie::Vector2 target) {
      uint16_t index;
      PathfinderHandle pathfinderHandle;
      handleList.create(&index, &pathfinderHandle);
      targets[index] = target;
      steeringHandles[index] = steeringHandle;
      bodyHandles[index] = bodyHandle;
      remainingRepathTimes[index] = 0;
      return pathfinderHandle;
    }

    void destroy(PathfinderHandle handle) {
      uint16_t sourceIndex, destinationIndex;
      handleList.destroy(handle, &sourceIndex, &destinationIndex);
      targets[destinationIndex] = targets[sourceIndex];
      steeringHandles[destinationIndex] = steeringHandles[sourceIndex];
      bodyHandles[destinationIndex] = bodyHandles[sourceIndex];
      remainingRepathTimes[destinationIndex] = remainingRepathTimes[sourceIndex];
      paths[destinationIndex] = paths[sourceIndex];
    }

    void updateSteering(uint16_t index) {
      Path *path = &paths[index];
      Fixie::Vector2 *nextWaypoint = &path->waypoints[path->nextWaypointIndex];
      Steering steering = SteeringSystem::get(steeringHandles[index]);
      (*steering.target)[0] = (*nextWaypoint)[0];
      (*steering.target)[1] = 0;
      (*steering.target)[2] = (*nextWaypoint)[1];
    }

    static Fixie::Num numHalf = Fixie::Num::inverse(2);
    void checkRepath() {
      for(uint16_t i=0; i<handleList.getCount(); ++i) {
        remainingRepathTimes[i] -= Config::tickDuration;
        if(remainingRepathTimes[i] <= 0) {
          remainingRepathTimes[i] += repathInterval;

          Physics::Body body = physicsEngine.getBody(bodyHandles[i]);

          MapFieldCoors origin = {
            (*body.position)[0]+numHalf,
            (*body.position)[2]+numHalf
          };
          MapFieldCoors target = {
            targets[i][0]+numHalf,
            targets[i][1]+numHalf
          };
          aStar(map, origin, target, mapSearchResult);
          // todo: proper handling of invalid paths
          assert(mapSearchResult.success);

          Path *path = &paths[i];
          path->reset();
          for(uint16_t n=0; n<mapSearchResult.count; ++n) {
            Fixie::Vector2 waypoint(mapSearchResult.path[n].x, mapSearchResult.path[n].y);
            path->add(waypoint);
          }

          updateSteering(i);

          mapSearchResult.reset();
        }
      }
    }

    void updateWaypoints() {
      for(uint16_t i=0; i<handleList.getCount(); ++i) {
        Path *path = &paths[i];
        uint16_t index = path->nextWaypointIndex;
        Fixie::Vector2 *nextWaypoint = &path->waypoints[index];
        Physics::Body body = physicsEngine.getBody(bodyHandles[i]);
        Fixie::Vector2 bodyPosition2D((*body.position)[0], (*body.position)[2]);
        Fixie::Vector2 difference = (*nextWaypoint)-bodyPosition2D;

        static Fixie::Num waypointDistanceToleranceSquared = Fixie::Num::inverse(16);
        if(difference.calcSquaredLength() <= waypointDistanceToleranceSquared && path->nextWaypointIndex+1 != path->count) {
          path->nextWaypointIndex++;
          updateSteering(i);
        }
      }
    }

    void update() {
      checkRepath();
      updateWaypoints();
    }
  }
}
