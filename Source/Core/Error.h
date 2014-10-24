#include <stdio.h>
#include <stdlib.h>

static void fatalError(const char *message) {
  printf("Game error:\n%s\n", message);
  exit(1);
}
