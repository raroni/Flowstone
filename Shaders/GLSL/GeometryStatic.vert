#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
layout(location = 3) in float selfIllumination;

layout(std140) uniform CameraTransforms {
  mat4 viewClipTransform;
  mat4 worldViewTransform;
};

flat out vec4 passedAppearance;
flat out vec3 passedNormal;

uniform mat4 modelWorldTransform;

void main() {
  gl_Position = viewClipTransform*worldViewTransform*modelWorldTransform*vec4(position, 1);

  vec3 worldNormal = (modelWorldTransform*vec4(normal, 0)).xyz; // assuming no scaling

  passedAppearance = vec4(color, selfIllumination);
  passedNormal = worldNormal;
}
