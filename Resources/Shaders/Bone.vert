#version 330

layout(location = 0) in vec3 position;
layout(location = 2) in uint jointIndex;

layout(std140) uniform global {
  mat4 viewClipTransformation;
  mat4 worldViewTransformation;
};

uniform mat4 jointWorldTransformation;
uniform mat4 modelJointTransformations[8];

void main() {
  vec4 jointPosition = modelJointTransformations[jointIndex]*vec4(position, 1);
  gl_Position = viewClipTransformation*worldViewTransformation*jointWorldTransformation*jointPosition;
}
