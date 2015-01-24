#version 330

in vec4 viewPosition;

out vec2 result;

void main() {
  float linearDepth = viewPosition.z;
  result = vec2(linearDepth, linearDepth*linearDepth);
}
