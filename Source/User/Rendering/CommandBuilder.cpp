#include "Core/Error.h"
#include "Rendering/ObjectIDCaster.h"
#include "Rendering/Object.h"
#include "Rendering/CommandSorter.h"
#include "Rendering/BoneMeshInstanceList.h"
#include "Rendering/CommandBuilder.h"

namespace Rendering {
  CommandBuilder::CommandBuilder(CommandSorter &commandSorter, BoneMeshInstanceList &boneMeshInstanceList, Quanta::Transform &cameraTransform) :
  commandSorter(commandSorter),
  boneMeshInstanceList(boneMeshInstanceList),
  cameraTransform(cameraTransform) { }

  void CommandBuilder::build(const Object *objects, const ObjectIndex *indices, uint16_t count) {
    enqueueUpdateWorldViewTransform();

    for(uint16_t i=0; count>i; i++) {
      const Object &object = objects[i];
      switch(object.type) {
        case ObjectType::BoneMeshInstance: {
          BoneMeshInstanceIndex index = ObjectIDCaster::createByBoneMeshInstanceIndex(object.id);
          enqueueBoneMeshInstanceDraw(index);
          break;
        }
        default: {
          fatalError("Could not resolve type.");
          break;
        }
      }
    }
  }

  void CommandBuilder::enqueueUpdateWorldViewTransform() {
    UpdateWorldViewTransformCommand command;
    Quanta::Matrix4 matrix = cameraTransform.getInverseMatrix();
    memcpy(command.matrix, matrix.components, sizeof(matrix.components));
    OrderKey key = {};
    key.layer = 1;
    commandSorter.writeUpdateWorldViewTransform(command, key);
  }

  void CommandBuilder::enqueueBoneMeshInstanceDraw(BoneMeshInstanceIndex index) {
    enqueueShaderProgramChange(ShaderName::Animated);
    BoneMeshInstance &instance = boneMeshInstanceList.get(index);
    DrawBoneMeshCommand command;
    command.meshIndex = instance.meshIndex;
    command.transform = transforms[instance.transformIndex];
    command.pose = poses[instance.transformIndex];
    OrderKey key = {};
    key.layer = 2;
    commandSorter.writeDrawBoneMesh(command, key);
  }

  void CommandBuilder::enqueueShaderProgramChange(ShaderName shader) {
    OrderKey key = {};
    key.layer = 0;
    ChangeShaderProgramCommand command;
    command.shader = shader;
    commandSorter.writeChangeShaderProgram(command, key);
  }
}
