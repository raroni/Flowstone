#version 330

in float linearDepth;

out vec2 result;

void main() {
  result = vec2(linearDepth, linearDepth*linearDepth);
}
