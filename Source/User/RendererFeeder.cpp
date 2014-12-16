#include "Core/Physics/Engine.h"
#include "Core/Physics/DynamicBody.h"
#include "Core/Physics/StaticBody.h"
#include "FrameInterpolator.h"
#include "Rendering/Renderer.h"
#include "Rendering/BoneMeshInstance.h"
#include "RendererFeeder.h"

RendererFeeder::RendererFeeder(
  const Physics::Engine &physicsEngine,
  const FrameInterpolator &interpolator,
  const Animation::Animator &animator,
  Rendering::Renderer &renderer) :
physicsEngine(physicsEngine),
interpolator(interpolator),
animator(animator),
renderer(renderer) { }

void RendererFeeder::update() {
  const Quanta::Matrix4* interpolatedTransforms = interpolator.getTransforms();
  for(uint8_t i=0; dynamicBoneBindings.count>i; i++) {
    DynamicBoneBinding &binding = dynamicBoneBindings.list[i];
    Rendering::BoneMeshInstance &instance = renderer.getBoneMeshInstance(binding.mesh);
    instance.transform = interpolatedTransforms[binding.interpolation];
    // instance.pose = x; TODO
  }

  const Quanta::Matrix4 *staticTransforms = physicsEngine.getStaticTransforms();
  for(uint8_t i=0; staticStaticBindings.count>i; i++) {
    StaticStaticBinding &binding = staticStaticBindings.list[i];
    renderer.updateStaticMeshTransform(binding.mesh, staticTransforms[binding.body]);
  }
}

void RendererFeeder::bindDynamicBone(uint8_t interpolation, Rendering::BoneMeshInstanceIndex mesh) {
  DynamicBoneBinding binding;
  binding.interpolation = interpolation;
  binding.mesh = mesh;
  dynamicBoneBindings.list[dynamicBoneBindings.count] = binding;
  dynamicBoneBindings.count++;
}

void RendererFeeder::bindStaticStatic(Physics::StaticBodyIndex body, Rendering::StaticMeshInstanceIndex mesh) {
  StaticStaticBinding binding;
  binding.body = body;
  binding.mesh = mesh;
  staticStaticBindings.list[staticStaticBindings.count] = binding;
  staticStaticBindings.count++;
}
