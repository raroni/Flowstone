attribute vec3 modelPosition;

void main() {
    gl_Position = vec4(modelPosition, 1);
}
