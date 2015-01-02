#version 330

out float result;
in vec2 texCoords;

uniform sampler2D noise;
uniform sampler2D depth;
uniform sampler2D normal;

uniform mat4 worldViewTransform;
uniform mat4 viewClipTransform;
uniform mat4 clipWorldTransform;
uniform vec2 noiseScale;
uniform float sampleRadius;

const int sampleKernelSize = 16;
uniform vec3 sampleKernel[sampleKernelSize];

void main() {
  float aDepth = texture(depth, texCoords).r;
  vec3 ndcPosition = vec3(texCoords, aDepth)*2-1;
  vec4 a = clipWorldTransform * vec4(ndcPosition, 1.0);
  vec4 worldPosition = vec4(a.xyz/a.w, 1);

  vec3 worldNormal = texture(normal, texCoords).xyz;
  vec3 viewPosition = (worldViewTransform * worldPosition).xyz;
  vec3 viewNormal = (worldViewTransform * vec4(worldNormal, 0)).xyz; // assuming no scaling

  vec3 randomVector = texture(noise, texCoords * noiseScale).xyz;
  vec3 tangent = normalize(randomVector - viewNormal * dot(randomVector, viewNormal));
  vec3 bitangent = cross(viewNormal, tangent);
  mat3 normalOrthoBasis = mat3(tangent, bitangent, viewNormal);

  float occlusion = 0.0;
  for(int i=0; i<sampleKernelSize; ++i) {
    vec3 sample = normalOrthoBasis * sampleKernel[i];
    sample = sample * sampleRadius + viewPosition;

    vec4 offset = vec4(sample, 1.0);
    offset = viewClipTransform * offset;
    offset.xy /= offset.w;

    // The depth texture comparison only work for coordinates inside the NDC unit square.
    // In practice this was only an issue for pixels near the top of the screen.
    if(offset.y > 1) continue;

    offset.xy = offset.xy * 0.5 + 0.5;

    float sampleNDCDepth = texture(depth, offset.xy).r*2-1;
    float zNear = 4.5;
    float zFar = 10.0;
    float sampleViewDepth = 2.0 * zNear * zFar / (zFar + zNear - sampleNDCDepth * (zFar - zNear));

    if(abs(viewPosition.z - sampleViewDepth) < sampleRadius && sampleViewDepth <= sample.z) {
      occlusion += 1;
    }
  }
  occlusion = 1.0-(occlusion/sampleKernelSize);

  result = occlusion;
}
