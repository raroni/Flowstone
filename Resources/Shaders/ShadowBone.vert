#version 330

layout(location = 0) in vec3 position;
layout(location = 3) in uint jointIndex;

uniform mat4 worldClipTransform;
uniform mat4 jointWorldTransform;
uniform mat4 modelJointTransforms[8];

void main() {
  vec4 jointPosition = modelJointTransforms[jointIndex] * vec4(position, 1);
  gl_Position = worldClipTransform * jointWorldTransform * jointPosition;
}