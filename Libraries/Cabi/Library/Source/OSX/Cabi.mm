#include <Foundation/Foundation.h>
#include "Cabi/Cabi.h"

static char pathBuffer[512];

static void fatalError(const char *message) {
  printf("Cabi error:\n%s\n", message);
  exit(1);
}

void readResourcesPath(char *buffer) {
  NSString *path = [[NSBundle mainBundle] resourcePath];
  strcpy(buffer, [path UTF8String]);
}

void cabiReadFile(const char *name, char *buffer, size_t bufferLength) {
  readResourcesPath(pathBuffer);
  strcat(pathBuffer, "/");
  strcat(pathBuffer, name);

  FILE *file = fopen(pathBuffer, "r");
  if(file == NULL) {
    fatalError("Could not read file.");
  }
  fread(buffer, 1, bufferLength, file);
  fclose(file);

  pathBuffer[0] = '\0';
}
