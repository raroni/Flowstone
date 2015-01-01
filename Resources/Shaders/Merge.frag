#version 330

out vec3 fragColor;
in vec2 texCoords;

uniform sampler2D diffuse;
uniform sampler2D normal;
uniform sampler2D depth;
uniform sampler2D shadow;
uniform sampler2D noise;

uniform mat4 cameraClipWorldTransform;
uniform mat4 cameraWorldViewTransform;
uniform mat4 cameraViewClipTransform;
uniform mat4 lightWorldClipTransform;
uniform vec3 inversePrimaryLightDirection;
uniform vec3 primaryLightColor;
uniform vec3 inverseSecondaryLightDirection;

const int sampleKernelSize = 16;
uniform vec3 sampleKernel[sampleKernelSize];

void main() {
  float aDepth = texture(depth, texCoords).r;
  vec3 fragmentNDCPosition = vec3(texCoords, aDepth)*2-1;
  vec4 a = cameraClipWorldTransform * vec4(fragmentNDCPosition, 1.0);
  vec4 fragmentWorldPosition = vec4(a.xyz/a.w, 1);
  vec4 lightClipPosition = lightWorldClipTransform * fragmentWorldPosition;
  vec3 lightNDCPosition = lightClipPosition.xyz/lightClipPosition.w;

  float primaryLuminosity;
  vec3 worldNormal = texture(normal, texCoords).xyz;
  if(dot(inversePrimaryLightDirection, worldNormal) < 0.01) {
    primaryLuminosity = 0;
  }
  else if(lightNDCPosition.z*0.5+0.5 > texture(shadow, lightNDCPosition.xy*0.5+0.5).x) {
    primaryLuminosity = 0;
  } else {
    primaryLuminosity = dot(inversePrimaryLightDirection, worldNormal);
  }

  float secondaryLuminosity = dot(inverseSecondaryLightDirection, worldNormal);

  vec3 fragmentCameraViewPosition = (cameraWorldViewTransform * fragmentWorldPosition).xyz;
  vec3 fragmentCameraViewNormal = (cameraWorldViewTransform * vec4(worldNormal, 0)).xyz; // assuming no scaling

  vec2 noiseScale = vec2(800.0/4.0, 600.0/4.0); // todo: precalc this
  vec3 randomVector = texture(noise, texCoords * noiseScale).xyz;
  vec3 tangent = normalize(randomVector - fragmentCameraViewNormal * dot(randomVector, fragmentCameraViewNormal));
  vec3 bitangent = cross(fragmentCameraViewNormal, tangent);
  mat3 normalOrthoBasis = mat3(tangent, bitangent, fragmentCameraViewNormal);

  float sampleRadius = 0.5f; // todo: is this required or not? If yes, convert to uniform
  float occlusion = 0.0;
  for(int i=0; i<sampleKernelSize; ++i) {
    vec3 sample = normalOrthoBasis * sampleKernel[i];
    sample = sample * sampleRadius + fragmentCameraViewPosition;

    vec4 offset = vec4(sample, 1.0);
    offset = cameraViewClipTransform * offset;
    offset.xy /= offset.w;
    offset.xy = offset.xy * 0.5 + 0.5;

    float sampleNDCDepth = texture(depth, offset.xy).r*2-1;
    float zNear = 4.5;
    float zFar = 10.0;
    float sampleViewDepth = 2.0 * zNear * zFar / (zFar + zNear - sampleNDCDepth * (zFar - zNear));

    if(abs(fragmentCameraViewPosition.z - sampleViewDepth) < sampleRadius) {
      occlusion += (sampleViewDepth <= sample.z ? 1.0 : 0.0);
    }
  }
  occlusion = 1.0-(occlusion/sampleKernelSize);

  vec3 atmosphereInfluence = primaryLightColor * (0.5*occlusion + 0.4*primaryLuminosity + 0.1*secondaryLuminosity);

  fragColor = texture(diffuse, texCoords).rgb * atmosphereInfluence;
}
