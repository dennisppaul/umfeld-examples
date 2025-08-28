#version 330 core

layout(location=0) in vec4 aPosition;
layout(location=3) in vec2 aTexCoord;

uniform mat4 uProjection;
uniform mat4 uViewMatrix; 
uniform mat4 uModelMatrix;

out vec2 vTexCoord;

void main() {
    gl_Position = uProjection * uViewMatrix * uModelMatrix * aPosition;
    vTexCoord = aTexCoord;
}
