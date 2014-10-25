attribute vec3 position;

uniform mat4 viewClipTransformation;

void main() {
  gl_Position = viewClipTransformation*vec4(position, 1);
}
