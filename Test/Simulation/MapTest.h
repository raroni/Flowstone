#include "Orwell.h"
#include "Simulation/Pathfinding/Map.h"

namespace SimulationMapTest {
  using namespace Orwell::Assertions;
  using namespace Simulation;

  static void assertDirectionListContains(MapFieldIndex field, Fixie::Num cost, const MapDirectionList &directions) {
    bool found = false;
    uint8_t i;
    for(i=0; i<directions.count; ++i) {
      if(directions.destinations[i] == field) {
        found = true;
        break;
      }
    }
    assertTrue(found);
    if(found) {
      assertInDelta(directions.costs[i], 0.01, cost);
    }
  }

  static void updateMap(Map &map, MapFieldType *types) {
    for(MapFieldIndex i=0; i<map.getSize().calcFieldCount(); ++i) {
      if(types[i] != MapFieldType::Grass) {
        map.set(i, types[i]);
      }
    }
  }

  void testDirectionsUponReset() {
    Map map;
    MapFieldType o = MapFieldType::Grass;
    MapFieldType x = MapFieldType::Tree;
    MapFieldType fields[] = {
      x, x, o,
      o, o, o,
      o, o, x
    };
    map.reset(3, 3, fields);

    MapFieldIndex center = map.calcFieldIndex({ 1, 1 });
    const MapDirectionList &directions = map.getDirections(center);

    MapFieldIndex down = map.calcFieldIndex({ 1, 2 });
    MapFieldIndex left = map.calcFieldIndex({ 0, 1 });
    MapFieldIndex right = map.calcFieldIndex({ 0, 1 });
    MapFieldIndex leftDown = map.calcFieldIndex({ 0, 2 });

    assertEqual(4, directions.count);
    assertDirectionListContains(down, 1, directions);
    assertDirectionListContains(left, 1, directions);
    assertDirectionListContains(right, 1, directions);
    assertDirectionListContains(leftDown, 1.4142, directions);
  }

  void testDirectionsUponSet() {
    Map map;
    MapFieldType grassFields[9] = { MapFieldType::Grass };
    map.reset(3, 3, grassFields);

    MapFieldType o = MapFieldType::Grass;
    MapFieldType x = MapFieldType::Tree;
    MapFieldType rockyFields[] = {
      o, o, o,
      o, o, o,
      o, x, x
    };
    updateMap(map, rockyFields);

    MapFieldIndex center = map.calcFieldIndex({ 1, 1 });
    const MapDirectionList &directions = map.getDirections(center);

    MapFieldIndex up = map.calcFieldIndex({ 1, 0 });
    MapFieldIndex left = map.calcFieldIndex({ 0, 1 });
    MapFieldIndex right = map.calcFieldIndex({ 2, 1 });
    MapFieldIndex upLeft = map.calcFieldIndex({ 0, 0 });
    MapFieldIndex upRight = map.calcFieldIndex({ 2, 0 });

    assertEqual(5, directions.count);
    assertDirectionListContains(up, 1, directions);
    assertDirectionListContains(left, 1, directions);
    assertDirectionListContains(right, 1, directions);
    assertDirectionListContains(upLeft, 1.4142, directions);
    assertDirectionListContains(upRight, 1.4142, directions);
  }

  void testDirectionsAtUpperLeft() {
    Map map;
    MapFieldType o = MapFieldType::Grass;
    MapFieldType x = MapFieldType::Tree;
    MapFieldType fields[] = {
      o, o, o,
      o, x, o,
      o, o, o
    };
    map.reset(3, 3, fields);

    MapFieldIndex upperLeft = map.calcFieldIndex({ 0, 0 });
    const MapDirectionList &directions = map.getDirections(upperLeft);

    MapFieldIndex right = map.calcFieldIndex({ 1, 0 });
    MapFieldIndex down = map.calcFieldIndex({ 0, 1 });

    assertEqual(2, directions.count);
    assertDirectionListContains(right, 1, directions);
    assertDirectionListContains(down, 1, directions);
  }

  void testDirectionsAtLowerRight() {
    Map map;
    MapFieldType o = MapFieldType::Grass;
    MapFieldType x = MapFieldType::Tree;
    MapFieldType fields[] = {
      x, x, x,
      x, o, o,
      x, o, o
    };
    map.reset(3, 3, fields);

    MapFieldIndex lowerRight = map.calcFieldIndex({ 2, 2 });
    const MapDirectionList &directions = map.getDirections(lowerRight);

    MapFieldIndex left = map.calcFieldIndex({ 1, 2 });
    MapFieldIndex up = map.calcFieldIndex({ 2, 1 });
    MapFieldIndex upLeft = map.calcFieldIndex({ 1, 1 });

    assertEqual(3, directions.count);
    assertDirectionListContains(left, 1, directions);
    assertDirectionListContains(up, 1, directions);
    assertDirectionListContains(upLeft, 1.4142, directions);
  }

  void setup() {
    unsigned group = Orwell::createGroup("SimulationMap");
    Orwell::addTest(group, testDirectionsUponReset, "DirectionsUponReset");
    Orwell::addTest(group, testDirectionsUponSet, "DirectionsUponSet");
    Orwell::addTest(group, testDirectionsAtUpperLeft, "DirectionsAtUpperLeft");
    Orwell::addTest(group, testDirectionsAtLowerRight, "DirectionsAtLowerRight");
  }
}
