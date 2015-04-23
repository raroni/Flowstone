#include "Physics/Engine.h"
#include "Simulation/PhysicsHack.h"
#include "Interpolation/Interpolater.h"
#include "Animation/Animator.h"
#include "Rendering/Renderer.h"
#include "Rendering/BoneMeshInstance.h"
#include "Client/MathConversion.h"
#include "RendererFeeder.h"

namespace Client {
  RendererFeeder::RendererFeeder(
    const Interpolation::Interpolater &interpolator,
    const Animation::Animator &animator,
    Rendering::Renderer &renderer) :
  interpolator(interpolator),
  animator(animator),
  renderer(renderer) { }

  void RendererFeeder::update() {
    const Quanta::Matrix4* interpolatedTransforms = interpolator.getTransforms();
    const Pose *poses = animator.getWorldPoses();
    for(uint16_t i=0; i<boneBindings.count; ++i) {
      BoneBinding &binding = boneBindings.list[i];
      Rendering::BoneMeshInstance instance = renderer.getBoneMeshInstance(binding.mesh);
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
