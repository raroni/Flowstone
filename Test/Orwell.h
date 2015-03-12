#ifndef ORWELL_H
#define ORWELL_H

#include <assert.h>
#include <string.h>
#include <stdio.h>

namespace Orwell {
  const static unsigned maxNameLength = 32;
  const static unsigned maxSuites = 32;
  char suiteNames[maxSuites][maxNameLength];
  unsigned suiteCount = 0;

  typedef void (*TestFunction)();
  const static unsigned maxTests = 1024;
  TestFunction testFunctions[maxTests];
  char testNames[maxTests][maxNameLength];
  unsigned testSuites[maxTests];
  unsigned testFunctionsCount = 0;

  unsigned createSuite(const char *name) {
    assert(suiteCount != maxSuites);
    strncpy(suiteNames[suiteCount], name, maxNameLength);
    return suiteCount++;
  }

  unsigned currentTest;

  void addTest(unsigned suite, TestFunction func, const char *name) {
    assert(testFunctionsCount != maxTests);
    strncpy(testNames[testFunctionsCount], name, maxNameLength);
    testFunctions[testFunctionsCount] = func;
    testSuites[testFunctionsCount] = suite;
    testFunctionsCount++;
  }

  void start() {
    for(currentTest=0; testFunctionsCount>currentTest; currentTest++) {
      testFunctions[currentTest]();
    }
    printf("Orwell done.\n");
  }

  void reportFailure(const char *failure) {
    unsigned suite = testSuites[currentTest];
    printf("%s::%s\n", suiteNames[suite], testNames[currentTest]);
    printf("%s\n\n", failure);
  }

  namespace Assertions {
    void assertEqual(uint8_t expected, uint8_t actual) {
      if(actual != expected) {
        char message[64];
        sprintf(message, "%d was not %d.", actual, expected);
        reportFailure(message);
      }
    }

    void assertInDelta(float expected, float delta, float actual) {
      if(expected-delta > actual || expected+delta < actual) {
        char message[256];
        sprintf(message, "%f was not within %f+-%f.", actual, expected, delta);
        reportFailure(message);
      }
    }

    void assertFalse(bool result) {
      if(result != false) {
        char message[64];
        sprintf(message, "%d was not false.", result);
        reportFailure(message);
      }
    }

    void assertTrue(bool result) {
      if(result != true) {
        char message[64];
        sprintf(message, "%d was not true.", result);
        reportFailure(message);
      }
    }
  }
}

#endif
