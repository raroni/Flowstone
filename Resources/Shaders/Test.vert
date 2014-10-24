attribute vec2 modelPosition;

uniform vec4 color;
uniform mat3 modelWorldTransformation;
uniform mat3 worldViewTransformation;
uniform mat3 viewClipTransformation;

varying vec4 interpolatedColor;

void main() {
    mat3 modelClipTransformation = viewClipTransformation*worldViewTransformation*modelWorldTransformation;
    vec3 clipPosition = modelClipTransformation*vec3(modelPosition, 1);
    gl_Position = vec4(clipPosition.xy, 0, 1);
    interpolatedColor = color;
}
