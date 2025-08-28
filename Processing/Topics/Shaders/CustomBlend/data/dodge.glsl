#version 330 core

in vec2 vTexCoord;
out vec4 FragColor;

uniform sampler2D destSampler;  // GL_TEXTURE0
uniform sampler2D srcSampler;   // GL_TEXTURE1

void main(void) {
  vec2 st = vTexCoord;
  
  // 두 텍스처에서 색상 샘플링
  vec3 destColor = texture(destSampler, st).rgb;
  vec3 srcColor = texture(srcSampler, st).rgb;
  
  // 디버깅: 단순 믹스 (50:50)
  FragColor = vec4(mix(destColor, srcColor, 0.5), 1.0);
  
  // 원래 Dodge 블렌딩 (나중에 활성화)
  // FragColor = vec4(destColor / (1.0 - srcColor), 1.0);
}