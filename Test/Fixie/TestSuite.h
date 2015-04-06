#include "Fixie/NumTest.h"
#include "Fixie/TrigTest.h"
#include "Fixie/UtilTest.h"

namespace FixieTestSuite {
  void setup() {
    FixieNumTest::setup();
    FixieTrigTest::setup();
    FixieUtilTest::setup();
  }
}
