#include "Core/Error.h"
#include "Rendering2/ObjectIDCaster.h"
#include "Rendering2/Commands.h"
#include "Rendering2/Object.h"
#include "Rendering2/CommandStream.h"
#include "Rendering2/AnimatedMeshInstanceList.h"
#include "Rendering2/CommandBuilder.h"

namespace Rendering2 {
  CommandBuilder::CommandBuilder(CommandStream &stream, AnimatedMeshInstanceList &animatedMeshInstanceList) :
  stream(stream),
  animatedMeshInstanceList(animatedMeshInstanceList) { }

  void CommandBuilder::build(const Object *objects, const ObjectIndex *indices, uint16_t count) {
    for(uint16_t i=0; count>i; i++) {
      const Object &object = objects[i];
      switch(object.type) {
        case ObjectType::AnimatedMeshInstance: {
          AnimatedMeshInstanceIndex index = ObjectIDCaster::createByAnimatedMeshInstanceIndex(object.id);
          enqueueAnimatedMeshInstanceDraw(index);
          break;
        }
        default: {
          fatalError("Could not resolve type.");
          break;
        }
      }
    }
  }

  void CommandBuilder::enqueueAnimatedMeshInstanceDraw(AnimatedMeshInstanceIndex index) {
    AnimatedMeshInstance &instance = animatedMeshInstanceList.get(index);
    enqueueShaderProgramChange(ShaderName::Animated);
    DrawAnimatedMeshCommand command;
    command.meshIndex = instance.meshIndex;
    command.transform = transforms[instance.transformIndex];
    command.pose = poses[instance.transformIndex];
    OrderKey key;
    key.layer = 1;
    stream.writeDrawAnimatedMesh(command, key);
  }

  void CommandBuilder::enqueueShaderProgramChange(ShaderName shader) {
    ChangeShaderCommand command;
    command.shader = shader;
    OrderKey key;
    key.layer = 0;
    stream.writeChangeShader(command, key);
  }
}
