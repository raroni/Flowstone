#include "Orwell.h"
#include "Simulation/Pathfinding/Map.h"

namespace SimulationMapTest {
  using namespace Orwell::Assertions;
  using namespace Simulation;

  static void assertDirectionListContains(MapFieldIndex field, const MapDirectionList &directions) {
    bool found = false;
    for(uint8_t i=0; i<directions.count; ++i) {
      if(directions.destinations[i] == field) {
        found = true;
        break;
      }
    }
    assertTrue(found);
  }

  static void updateMap(Map &map, MapFieldType *types) {
    for(MapFieldIndex i=0; i<map.getSize(); ++i) {
      if(types[i] != MapFieldType::Grass) {
        map.set(i, types[i]);
      }
    }
  }

  void testOrthogonalDirectionsUponReset() {
    Map map;

    MapFieldType o = MapFieldType::Grass;
    MapFieldType x = MapFieldType::Rock;
    MapFieldType fields[] = {
      o, o, o, o, o,
      o, x, o, x, o,
      o, o, o, o, o,
      o, x, o, x, o,
      o, o, o, o, o
    };
    map.reset(5, 5, fields);

    MapFieldIndex center = map.calcFieldIndex({ 2, 2 });
    const MapDirectionList &directions = map.getDirections(center);

    MapFieldIndex up = map.calcFieldIndex({ 2, 1 });
    MapFieldIndex down = map.calcFieldIndex({ 2, 3 });
    MapFieldIndex left = map.calcFieldIndex({ 1, 2 });
    MapFieldIndex right = map.calcFieldIndex({ 3, 2 });

    assertEqual(4, directions.count);
    assertDirectionListContains(up, directions);
    assertDirectionListContains(down, directions);
    assertDirectionListContains(left, directions);
    assertDirectionListContains(right, directions);
  }

  void testOrthogonalDirectionsUponSet() {
    Map map;
    MapFieldType grassFields[25] = { MapFieldType::Grass };
    map.reset(5, 5, grassFields);

    MapFieldType o = MapFieldType::Grass;
    MapFieldType x = MapFieldType::Rock;
    MapFieldType rockyFields[] = {
      o, o, o, o, o,
      o, x, o, x, o,
      o, o, o, o, o,
      o, x, o, x, o,
      o, o, o, o, o
    };
    updateMap(map, rockyFields);

    MapFieldIndex center = map.calcFieldIndex({ 2, 2 });
    const MapDirectionList &directions = map.getDirections(center);

    MapFieldIndex up = map.calcFieldIndex({ 2, 1 });
    MapFieldIndex down = map.calcFieldIndex({ 2, 3 });
    MapFieldIndex left = map.calcFieldIndex({ 1, 2 });
    MapFieldIndex right = map.calcFieldIndex({ 3, 2 });

    assertEqual(4, directions.count);
    assertDirectionListContains(up, directions);
    assertDirectionListContains(down, directions);
    assertDirectionListContains(left, directions);
    assertDirectionListContains(right, directions);
  }

  void setup() {
    unsigned group = Orwell::createGroup("SimulationMapTest");
    Orwell::addTest(group, testOrthogonalDirectionsUponReset, "OrthogonalDirectionsUponReset");
    Orwell::addTest(group, testOrthogonalDirectionsUponSet, "OrthogonalDirectionsUponSet");
    // Todo:
    // test diago
    // test borders/limits
  }
}
