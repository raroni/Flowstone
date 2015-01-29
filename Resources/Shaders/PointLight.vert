#version 330

out vec4 worldPosition;
flat out float radius;
flat out vec3 center;

layout(location = 0) in vec3 position;

layout(std140) uniform CameraTransforms {
  mat4 viewClipTransform;
  mat4 worldViewTransform;
};

uniform mat4 modelWorldTransform;

void main() {
  worldPosition = modelWorldTransform*vec4(position, 1);
  gl_Position = viewClipTransform*worldViewTransform*worldPosition;
  center.x = modelWorldTransform[3][0];
  center.y = modelWorldTransform[3][1];
  center.z = modelWorldTransform[3][2];
  radius = modelWorldTransform[0][0];
}
