/**
 * Deform. 
 * 
 * A GLSL version of the oldschool 2D deformation effect, by Inigo Quilez.
 * Ported from the webGL version available in ShaderToy:
 * http://www.iquilezles.org/apps/shadertoy/
 * (Look for Deform under the Plane Deformations Presets)
 * 
 */

#include "Umfeld.h"
#include "PShader.h"

using namespace umfeld;

PImage* tex;
PShader* deform;

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)c
}

void setup() {
    texture_wrap(REPEAT); //@diff(textureWrap)
    tex = loadImage("tex1.jpg");

    deform = loadShader(loadString("passthrough.vert"), loadString("deform.glsl"));
    deform->set_uniform("resolution", float(width), float(height));
}

void draw() {
    background(0.5f);
    image(tex, 0, 0, width, height);
    
    deform->set_uniform("tex", 0);
    deform->set_uniform("time", millis() / 1000.f);
    deform->set_uniform("mouse", float(mouseX), float(mouseY));
    shader(deform);
    
    rect(0, 0, width, height);
}
