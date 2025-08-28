#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec4 color;
layout(location = 3) in vec3 texCoord;

uniform mat4 transform;
uniform mat4 texMatrix;

out vec4 vertColor;
out vec2 vTexCoord;

void main() {
  gl_Position = transform * position;
  
  vertColor = color;
  vTexCoord = (texMatrix * vec4(texCoord, 1.0)).xy;
}