#include "Core/Error.h"
#include "Rendering2/ObjectIDCaster.h"
#include "Rendering2/Object.h"
#include "Rendering2/CommandSorter.h"
#include "Rendering2/AnimatedMeshInstanceList.h"
#include "Rendering2/CommandBuilder.h"

namespace Rendering2 {
  CommandBuilder::CommandBuilder(CommandSorter &commandSorter, AnimatedMeshInstanceList &animatedMeshInstanceList) :
  commandSorter(commandSorter),
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
    enqueueShaderProgramChange(ShaderName::Animated);
    //AnimatedMeshInstance &instance = animatedMeshInstanceList.get(index);
    //DrawAnimatedMeshCommand command;
    //command.meshIndex = instance.meshIndex;
    //command.transform = transforms[instance.transformIndex];
    //command.pose = poses[instance.transformIndex];
    //OrderKey key;
    //key.layer = 1;
    //commandSorter.writeDrawAnimatedMesh(command, key);
  }

  void CommandBuilder::enqueueShaderProgramChange(ShaderName shader) {
    OrderKey key;
    key.layer = 0;
    commandSorter.writeType(CommandType::ChangeShaderProgram, key);
    commandSorter.writeShaderName(shader);
  }
}
