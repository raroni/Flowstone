
#include <OpenGL/gl.h>

void baseGraphicsInit() {
  glClearColor(1, 0, 0, 1);
}

void baseGraphicsClear() {
  glClear(GL_COLOR_BUFFER_BIT);
}
