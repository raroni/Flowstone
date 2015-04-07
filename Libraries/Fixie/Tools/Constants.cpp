#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "Fixie/Config.h"
#include "Fixie/Num.h"

int main() {
  const Fixie::Num pi = M_PI;
  const Fixie::Num pi2 = M_PI*2;
  const Fixie::Num rpi2 = 1.0 / (M_PI*2.0);

  printf("pi: %d\n", pi.raw);
  printf("pi2: %d\n", pi2.raw);
  printf("rpi2: %d\n", rpi2.raw);
}
