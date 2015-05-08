#include "Physics/Engine.h"
#include "Simulation/PhysicsHack.h"
#include "Animation/Animator.h"
#include "Rendering/Renderer.h"
#include "Rendering/BoneMeshInstance.h"
#include "Client/Interpolation.h"
#include "Client/MathConversion.h"
#include "RenderFeed.h"

namespace Client {
  namespace RenderFeed {
    struct BoneBinding {
      uint8_t interpolation;
      Animation::PoseHandle pose;
      Rendering::BoneMeshInstanceHandle mesh;
    };

    struct {
      BoneBinding list[128];
      uint8_t count = 0;
    } boneBindings;

    void update() {
      const Quanta::Matrix4* interpolatedTransforms = Interpolation::getTransforms();
      const Animation::Pose *poses = Animation::animator.getWorldPoses();
      for(uint16_t i=0; i<boneBindings.count; ++i) {
        BoneBinding &binding = boneBindings.list[i];
        Rendering::BoneMeshInstance instance = Rendering::renderer.getBoneMeshInstance(binding.mesh);
        (*instance.transform) = interpolatedTransforms[binding.interpolation];
        (*instance.pose) = poses[binding.pose];
      }
    }

    uint16_t createBoneMeshFeed(InterpolationHandle interpolation, Animation::PoseHandle pose, Rendering::BoneMeshInstanceHandle mesh) {
      BoneBinding binding;
      binding.interpolation = interpolation;
      binding.mesh = mesh;
      binding.pose = pose;
      boneBindings.list[boneBindings.count] = binding;
      boneBindings.count++;
      return 0; // todo: fix
    }
  }
}
