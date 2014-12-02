#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in uint jointIndex;

layout(std140) uniform global {
  mat4 viewClipTransformation;
  mat4 worldViewTransformation;
};

out vec3 interpolatedColor;
out float interpolatedLambert;

uniform mat4 jointWorldTransformation;
uniform mat4 modelJointTransformations[8];

void main() {
  vec4 jointPosition = modelJointTransformations[jointIndex]*vec4(position, 1);
  gl_Position = viewClipTransformation*worldViewTransformation*jointWorldTransformation*jointPosition;

  vec3 worldNormal = (jointWorldTransformation*vec4(normal, 0)).xyz; // assuming no scaling
  vec3 worldLightDirection = normalize(vec3(-1, -3, 1)*-1);
  interpolatedLambert = dot(worldLightDirection, worldNormal)*0.4+0.6;

  interpolatedColor = vec3(0, 1, 0);
}
