#include "Fixie/NumTest.h"
#include "Fixie/TrigTest.h"
#include "Fixie/UtilTest.h"
#include "Fixie/Vector3Test.h"
#include "Fixie/Matrix4Test.h"
#include "Fixie/QuaternionTest.h"

namespace FixieTestSuite {
  void setup() {
    FixieNumTest::setup();
    FixieTrigTest::setup();
    FixieUtilTest::setup();
    FixieVector3Test::setup();
    FixieMatrix4Test::setup();
    FixieQuaternionTest::setup();
  }
}
