#include "Physics/Engine.h"
#include "Physics/DynamicBody.h"
#include "Physics/StaticBody.h"
#include "Interpolation/Interpolater.h"
#include "Animation/Animator.h"
#include "Rendering/Renderer.h"
#include "Rendering/BoneMeshInstance.h"
#include "RendererFeeder.h"

namespace Client {
  RendererFeeder::RendererFeeder(
    const Physics::Engine &physicsEngine,
    const Interpolation::Interpolater &interpolator,
    const Animation::Animator &animator,
    Rendering::Renderer &renderer) :
  physicsEngine(physicsEngine),
  interpolator(interpolator),
  animator(animator),
  renderer(renderer) { }

  void RendererFeeder::update() {
    const Quanta::Matrix4* interpolatedTransforms = interpolator.getTransforms();
    const Pose *poses = animator.getWorldPoses();
    for(uint8_t i=0; dynamicBoneBindings.count>i; i++) {
      DynamicBoneBinding &binding = dynamicBoneBindings.list[i];
      Rendering::BoneMeshInstance instance = renderer.getBoneMeshInstance(binding.mesh);
      (*instance.transform) = interpolatedTransforms[binding.interpolation];
      (*instance.pose) = poses[binding.pose];
    }

    const Quanta::Matrix4 *staticTransforms = physicsEngine.getStaticTransforms();
    for(uint8_t i=0; staticStaticBindings.count>i; i++) {
      StaticStaticBinding &binding = staticStaticBindings.list[i];
      renderer.updateStaticMeshTransform(binding.mesh, staticTransforms[binding.body]);
    }
  }

  void RendererFeeder::setupBoneMesh(Interpolation::Index interpolation, Animation::PoseIndex pose, Rendering::BoneMeshInstanceHandle mesh) {
    DynamicBoneBinding binding;
    binding.interpolation = interpolation;
    binding.mesh = mesh;
    binding.pose = pose;
    dynamicBoneBindings.list[dynamicBoneBindings.count] = binding;
    dynamicBoneBindings.count++;
  }

  void RendererFeeder::bindStaticStatic(Physics::StaticBodyIndex body, Rendering::StaticMeshInstanceHandle mesh) {
    StaticStaticBinding binding;
    binding.body = body;
    binding.mesh = mesh;
    staticStaticBindings.list[staticStaticBindings.count] = binding;
    staticStaticBindings.count++;
  }
}
