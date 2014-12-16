#include "Core/Physics/Engine.h"
#include "Core/Physics/DynamicBody.h"
#include "Core/Physics/StaticBody.h"
#include "FrameInterpolator.h"
#include "Rendering/Renderer.h"
#include "Rendering/BoneMeshInstance.h"
#include "PhysicsRenderingLink.h"

PhysicsRenderingLink::PhysicsRenderingLink(const Physics::Engine &physicsEngine, Rendering::Renderer &renderer, const FrameInterpolator &interpolator) :
physicsEngine(physicsEngine),
interpolator(interpolator),
renderer(renderer) { }

void PhysicsRenderingLink::update() {
  const Quanta::Matrix4* transforms = interpolator.getTransforms();
  for(uint8_t i=0; dynamicBoneBindings.count>i; i++) {
    DynamicBoneBinding &binding = dynamicBoneBindings.list[i];
    renderer.updateBoneMeshTransform(binding.mesh, transforms[binding.interpolation]);
  }

  const Quanta::Matrix4 *staticTransforms = physicsEngine.getStaticTransforms();
  for(uint8_t i=0; staticStaticBindings.count>i; i++) {
    StaticStaticBinding &binding = staticStaticBindings.list[i];
    renderer.updateStaticMeshTransform(binding.mesh, staticTransforms[binding.body]);
  }
}

void PhysicsRenderingLink::bindDynamicBone(uint8_t interpolation, Rendering::BoneMeshInstanceIndex mesh) {
  DynamicBoneBinding binding;
  binding.interpolation = interpolation;
  binding.mesh = mesh;
  dynamicBoneBindings.list[dynamicBoneBindings.count] = binding;
  dynamicBoneBindings.count++;
}

void PhysicsRenderingLink::bindStaticStatic(Physics::StaticBodyIndex body, Rendering::StaticMeshInstanceIndex mesh) {
  StaticStaticBinding binding;
  binding.body = body;
  binding.mesh = mesh;
  staticStaticBindings.list[staticStaticBindings.count] = binding;
  staticStaticBindings.count++;
}
