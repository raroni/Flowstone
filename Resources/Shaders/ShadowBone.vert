#version 330

layout(location = 0) in vec3 position;
layout(location = 3) in uint jointIndex;

out float linearDepth;

uniform mat4 worldViewTransform;
uniform mat4 viewClipTransform;
uniform mat4 jointWorldTransform;
uniform mat4 modelJointTransforms[8];

void main() {
  vec4 worldPosition = jointWorldTransform * modelJointTransforms[jointIndex] * vec4(position, 1);
  linearDepth = worldPosition.z;
  gl_Position = viewClipTransform*worldViewTransform*worldPosition;
}
