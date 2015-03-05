#include <Foundation/Foundation.h>
#include "SysFile/SysFile.h"

static char pathBuffer[512];

static void fatalError(const char *message) {
  printf("SysFile error:\n%s\n", message);
  exit(1);
}

static void readResourcesPath(char *buffer) {
  NSString *path = [[NSBundle mainBundle] resourcePath];
  strcpy(buffer, [path UTF8String]);
}

namespace SysFile {
  void readFile(const char *name, char *buffer, size_t bufferLength) {
    readResourcesPath(pathBuffer);
    strcat(pathBuffer, "/");
    strcat(pathBuffer, name);

    FILE *file = fopen(pathBuffer, "r");
    if(file == NULL) {
      fatalError("Could not read file.");
    }
    size_t bytes = fread(buffer, 1, bufferLength, file);
    fclose(file);
    if(bytes == bufferLength) {
      fatalError("Buffer too small.");
    }
    buffer[bytes] = '\0';
    pathBuffer[0] = '\0';
  }
}
