#version 330

layout(location = 0) in vec3 position;
layout(location = 4) in uint jointIndex;

out vec4 viewPosition;

uniform mat4 worldViewTransform;
uniform mat4 viewClipTransform;
uniform mat4 jointWorldTransform;
uniform mat4 modelJointTransforms[8];

void main() {
  viewPosition = worldViewTransform*jointWorldTransform * modelJointTransforms[jointIndex] * vec4(position, 1);
  gl_Position = viewClipTransform*viewPosition;
}
