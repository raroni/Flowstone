#include <Foundation/Foundation.h>
#include "Cabi/Cabi.h"

static char pathBuffer[512];

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
    printf("Could not read file.");
    exit(1);
  }
  fread(buffer, 1, bufferLength, file);
  fclose(file);

  pathBuffer[0] = '\0';
}
