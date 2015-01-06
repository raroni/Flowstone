#version 330

in vec2 texCoords;

uniform sampler2D depthTexture;
uniform sampler2D normalTexture;

layout (location = 0) out float resultDepth;
layout (location = 1) out vec3 resultNormal;

void main() {
  resultDepth = texture(depthTexture, texCoords).x;
  resultNormal = texture(normalTexture, texCoords).xyz;
}
