#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 3) in uint jointIndex;

layout(std140) uniform global {
  mat4 viewClipTransform;
  mat4 worldViewTransform;
};

flat out vec3 passedColor;
flat out vec3 passedNormal;

uniform mat4 jointWorldTransform;
uniform mat4 modelJointTransforms[8];

void main() {
  vec4 jointPosition = modelJointTransforms[jointIndex]*vec4(position, 1);
  gl_Position = viewClipTransform*worldViewTransform*jointWorldTransform*jointPosition;

  vec3 worldNormal = (jointWorldTransform*vec4(normal, 0)).xyz; // assuming no scaling

  passedColor = vec3(0.3, 0.6, 0.95);
  passedNormal = worldNormal;
}
