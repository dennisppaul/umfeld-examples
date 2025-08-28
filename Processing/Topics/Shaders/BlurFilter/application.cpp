/**
 * Blur Filter
 * 
 * Change the default shader to apply a simple, custom blur filter.
 * 
 * Press the mouse to switch between the custom and default shader.
 */

#include "Umfeld.h"
#include "PShader.h"
// #include <GL/gl.h>
using namespace umfeld;

PShader* blur;

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {
    std::string vertexCode   = loadString("blur.vert");
    std::string fragmentCode = loadString("blur.glsl");
    blur = loadShader(vertexCode, fragmentCode);
    stroke(1.f, 0, 0); //@diff(color_range)
    rectMode(CENTER);
}

void draw() {
    background(0.5f); //@diff(color_range)
    rect(mouseX, mouseY, 150, 150);
    ellipse(mouseX, mouseY, 100, 100);
    
    blur->set_uniform("tex", 0);
    blur->set_uniform("texOffset", glm::vec2(1.0f/width, 1.0f/height));
    shader(blur);
    rect(0, 0, width, height);
}
