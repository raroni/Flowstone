#ifndef RENDERING_GEOMETRY_PASS_H
#define RENDERING_GEOMETRY_PASS_H

namespace Rendering {
  class CommandStream;
  struct DrawSet;

  namespace GeometryPass {
    void write(CommandStream &stream, const DrawSet &drawSet, const BoneMeshRegistry &boneMeshRegistry);
  }
}

#endif
