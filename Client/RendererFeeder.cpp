#include "Physics/Engine.h"
#include "Simulation/PhysicsHack.h"
#include "Interpolation/Interpolater.h"
#include "Animation/Animator.h"
#include "Rendering/Renderer.h"
#include "Rendering/BoneMeshInstance.h"
#include "Client/MathConversion.h"
#include "RendererFeeder.h"

namespace Client {
  void RendererFeeder::update() {
    const Quanta::Matrix4* interpolatedTransforms = Interpolation::interpolater.getTransforms();
    const Animation::Pose *poses = Animation::animator.getWorldPoses();
    for(uint16_t i=0; i<boneBindings.count; ++i) {
      BoneBinding &binding = boneBindings.list[i];
      Rendering::BoneMeshInstance instance = Rendering::renderer.getBoneMeshInstance(binding.mesh);
      (*instance.transform) = interpolatedTransforms[binding.interpolation];
      (*instance.pose) = poses[binding.pose];
    }
  }

  void RendererFeeder::setupBoneMesh(Interpolation::Index interpolation, Animation::PoseIndex pose, Rendering::BoneMeshInstanceHandle mesh) {
    BoneBinding binding;
    binding.interpolation = interpolation;
    binding.mesh = mesh;
    binding.pose = pose;
    boneBindings.list[boneBindings.count] = binding;
    boneBindings.count++;
  }
}
