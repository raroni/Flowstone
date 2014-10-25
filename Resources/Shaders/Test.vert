attribute vec3 position;

uniform mat4 worldViewTransformation;
uniform mat4 viewClipTransformation;

void main() {
  gl_Position = viewClipTransformation*worldViewTransformation*vec4(position, 1);
}
