/* 
 * this example is based on the Processing example
 * https://processing.org/reference/box_.html
 * and shows how to draw 3D primitives in umfeld.
 */

#include "Umfeld.h"

using namespace umfeld;

void settings() {
    size(400, 400);
}

void setup() {
    noFill();
    g->set_render_mode(RENDER_MODE_IMMEDIATELY);
    g->set_render_mode(RENDER_MODE_SORTED_BY_SUBMISSION_ORDER);
    g->set_render_mode(RENDER_MODE_SORTED_BY_Z_ORDER);

    g->set_stroke_render_mode(STROKE_RENDER_MODE_NATIVE);
    g->set_stroke_render_mode(STROKE_RENDER_MODE_TRIANGULATE_2D);

    profile(PROFILE_3D);
}

void draw() {
    TRACE_FRAME;

    background(0.85f);
    strokeWeight(3);

    stroke(0.5f, 0.85f, 1.0f);
    noFill();
    pushMatrix();
    translate(232, 192, 0);
    rotateY(0.5f);
    box(160);
    popMatrix();

    stroke(1.0f, 0.25f, 0.35f);
    noFill();
    pushMatrix();
    translate(232, 192, 0);
    rotateY(0.5);
    box(160, 80, 200);
    popMatrix();

    stroke(1.0f);
    fill(mouseX / width * 2, 0, 0.62f); // NOTE stroke+filled shapes in render mode 'RENDER_MODE_SORTED_BY_Z_ORDER' do not play well with stroke render mode 'STROKE_RENDER_MODE_TRIANGULATE_2D'
    translate(200, 200, 0);
    rotateX(mouseY * 0.05);
    rotateZ(mouseX * 0.05);
    sphereDetail(mouseX / 4);
    sphere(100);
}

void keyPressed() {
    if (key == ' ') {
        static bool toggle_render_mode = true;
        toggle_render_mode             = !toggle_render_mode;
        if (toggle_render_mode) {
            g->set_render_mode(RENDER_MODE_SORTED_BY_SUBMISSION_ORDER);
            console("RENDER_MODE_SORTED_BY_SUBMISSION_ORDER");
        } else {
            g->set_render_mode(RENDER_MODE_SORTED_BY_Z_ORDER);
            console("RENDER_MODE_SORTED_BY_Z_ORDER");
        }
    }
    if (key == 's') {
        static bool toggle_stroke_render_mode = true;
        toggle_stroke_render_mode             = !toggle_stroke_render_mode;
        if (toggle_stroke_render_mode) {
            g->set_stroke_render_mode(STROKE_RENDER_MODE_TRIANGULATE_2D);
            console("STROKE_RENDER_MODE_TRIANGULATE_2D");
        } else {
            g->set_stroke_render_mode(STROKE_RENDER_MODE_NATIVE);
            console("STROKE_RENDER_MODE_NATIVE");
        }
    }
}
