#version 330 core

in vec2 vTexCoord;
out vec4 FragColor;

uniform sampler2D tex;
uniform vec2 texOffset;

void main(void) {
  // Grouping texcoord variables in order to make it work in the GMA 950. See post #13
  // in this thread:
  // http://www.idevgames.com/forums/thread-3467.html
  vec2 tc0 = vTexCoord.st + vec2(-texOffset.s, -texOffset.t);
  vec2 tc1 = vTexCoord.st + vec2(         0.0, -texOffset.t);
  vec2 tc2 = vTexCoord.st + vec2(+texOffset.s, -texOffset.t);
  vec2 tc3 = vTexCoord.st + vec2(-texOffset.s,          0.0);
  vec2 tc4 = vTexCoord.st + vec2(         0.0,          0.0);
  vec2 tc5 = vTexCoord.st + vec2(+texOffset.s,          0.0);
  vec2 tc6 = vTexCoord.st + vec2(-texOffset.s, +texOffset.t);
  vec2 tc7 = vTexCoord.st + vec2(         0.0, +texOffset.t);
  vec2 tc8 = vTexCoord.st + vec2(+texOffset.s, +texOffset.t);

  vec4 col0 = texture(tex, tc0);
  vec4 col1 = texture(tex, tc1);
  vec4 col2 = texture(tex, tc2);
  vec4 col3 = texture(tex, tc3);
  vec4 col4 = texture(tex, tc4);
  vec4 col5 = texture(tex, tc5);
  vec4 col6 = texture(tex, tc6);
  vec4 col7 = texture(tex, tc7);
  vec4 col8 = texture(tex, tc8);

  vec4 sum = (1.0 * col0 + 2.0 * col1 + 1.0 * col2 +  
              2.0 * col3 + 4.0 * col4 + 2.0 * col5 +
              1.0 * col6 + 2.0 * col7 + 1.0 * col8) / 16.0;            
  FragColor = vec4(sum.rgb, 1.0);  
}