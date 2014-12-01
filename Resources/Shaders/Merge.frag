#version 330

out vec3 fragColor;
in vec2 texCoords;

uniform sampler2D diffuse;
uniform sampler2D lambert;

void main() {
  fragColor = texture(diffuse, texCoords).rgb * texture(lambert, texCoords).r;
}
