#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 4) in uint jointIndex;

layout(std140) uniform CameraTransforms {
  mat4 viewClipTransform;
  mat4 worldViewTransform;
};

flat out vec4 passedAppearance;
flat out vec3 passedNormal;

uniform mat4 jointWorldTransform;
uniform mat4 modelJointTransforms[8];

void main() {
  vec4 jointPosition = modelJointTransforms[jointIndex]*vec4(position, 1);
  gl_Position = viewClipTransform*worldViewTransform*jointWorldTransform*jointPosition;

  vec3 worldNormal = (jointWorldTransform*vec4(normal, 0)).xyz; // assuming no scaling

  passedAppearance = vec4(0.3, 0.6, 0.95, 0);
  passedNormal = worldNormal;
}
