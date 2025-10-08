/*
 * this example shows how to use the beginShape() + endShape() functions to draw a shape with different vertex types.
 * from https://processing.org/reference/beginShape_.html
 */

#include "Umfeld.h"
#include "Geometry.h"

using namespace umfeld;

const color_32 light_blue = color(0.5, 0.85, 1.0);
const color_32 soft_red   = color(1.0, 0.25, 0.35);

int   stroke_join_mode = ROUND;
int   stroke_cap_mode  = ROUND;
float stroke_weight    = 15.0f;

void settings() {
    size(1024, 768);
}

void setup() {}

void draw() {
    background(0.85);

    fill(0);
    debug_text("FPS: " + nf(frameRate, 1), 10, 10);
    debug_text(nf(mouseX, 0) + ", " + nf(mouseY, 0), 10, 20);

    stroke(0.0f);
    fill_color_32(light_blue);
    strokeWeight(stroke_weight);
    pointSize(stroke_weight);
    strokeJoin(stroke_join_mode);
    strokeCap(stroke_cap_mode);

    scale(0.66667f);

    beginShape();
    vertex(120, 80);
    vertex(340, 80);
    vertex(340, 300);
    vertex(120, 300);
    endShape(CLOSE);

    translate(280, 0);
    beginShape(POINTS);
    vertex(120, 80);
    vertex(340, 80);
    vertex(340, 300);
    vertex(120, 300);
    endShape();

    translate(280, 0);
    beginShape();
    vertex(120, 80);
    vertex(230, 80);
    vertex(230, 190);
    vertex(340, 190);
    vertex(340, 300);
    vertex(120, 300);
    endShape(CLOSE);

    translate(280, 0);
    beginShape(LINES);
    vertex(120, 80);
    vertex(340, 80);
    vertex(340, 300);
    vertex(120, 300);
    endShape();

    translate(-4 * 280, 280);

    translate(280, 0);
    noFill();
    beginShape();
    vertex(120, 80);
    vertex(340, 80);
    vertex(340, 300);
    vertex(120, 300);
    endShape();

    translate(280, 0);
    noFill();
    beginShape();
    vertex(120, 80);
    vertex(340, 80);
    vertex(340, 300);
    vertex(120, 300);
    endShape(CLOSE);

    stroke(0.0f);
    fill_color_32(soft_red);

    translate(280, 0);
    beginShape(TRIANGLES); // TODO disconnected triangles cause line artifacts
    vertex(120, 300);
    vertex(160, 120);
    vertex(200, 300);
    vertex(270, 80);
    vertex(280, 300);
    vertex(320, 80);
    endShape();

    translate(280, 0);
    beginShape(TRIANGLE_STRIP);
    vertex(120, 300);
    vertex(160, 80);
    vertex(200, 300);
    vertex(240, 80);
    vertex(280, 300);
    vertex(320, 80);
    vertex(360, 300);
    endShape();

    translate(-4 * 280, 280);

    translate(280, 0);
    beginShape(TRIANGLE_FAN);
    vertex(230, 200);
    vertex(230, 60);
    vertex(368, 200);
    vertex(230, 340);
    vertex(88, 200);
    vertex(230, 60);
    endShape();

    translate(280, 0);
    beginShape(QUAD_STRIP);
    vertex(120, 80);
    vertex(120, 300);
    vertex(200, 80);
    vertex(200, 300);
    vertex(260, 80);
    vertex(260, 300);
    vertex(340, 80);
    vertex(340, 300);
    endShape();

    translate(280, 0);
    pushMatrix();
    translate(120, 80);
    rotateY((float) frameCount * 0.027f);
    rotateZ((float) frameCount * 0.01f);
    translate(-120, -80);
    beginShape(LINE_STRIP);
    vertex(120, 80);
    vertex(120, 300);
    vertex(200, 300);
    vertex(200, 80);
    vertex(260, 80);
    vertex(260, 300);
    vertex(340, 300);
    vertex(340, 80);
    endShape();
    popMatrix();

    translate(280, 0);
    circle(230, 190, 220);

    translate(280, 0);
    bezier(120, 80 - 560, 120, 300 - 560, 340, 80, 340, 300);
}

void keyPressed() {
    if (key == '-') {
        stroke_weight -= 0.25f;
        if (stroke_weight < 0) { stroke_weight = 0; }
        strokeWeight(stroke_weight);
        console("stroke_weight: ", stroke_weight);
    }
    if (key == '+') {
        stroke_weight += 0.25f;
        strokeWeight(stroke_weight);
        console("stroke_weight: ", stroke_weight);
    }
    if (key == '1') {
        stroke_join_mode = NONE;
        strokeJoin(NONE);
        console("NONE");
    }
    if (key == '2') {
        stroke_join_mode = BEVEL;
        strokeJoin(BEVEL);
        console("BEVEL");
    }
    if (key == '3') {
        stroke_join_mode = MITER;
        strokeJoin(MITER);
        console("MITER");
    }
    if (key == '4') {
        stroke_join_mode = ROUND;
        strokeJoin(ROUND);
        console("ROUND");
    }
    if (key == '5') {
        stroke_join_mode = MITER_FAST;
        strokeJoin(MITER_FAST);
        console("MITER_FAST");
    }
    if (key == '6') {
        stroke_join_mode = BEVEL_FAST;
        strokeJoin(BEVEL_FAST);
        console("BEVEL_FAST");
    }
    if (key == 'q') {
        stroke_cap_mode = POINTED;
        strokeCap(POINTED);
        console("POINTED");
    }
    if (key == 'w') {
        stroke_cap_mode = PROJECT;
        strokeCap(PROJECT);
        console("PROJECT");
    }
    if (key == 'e') {
        stroke_cap_mode = ROUND;
        strokeCap(ROUND);
        console("ROUND");
    }
    if (key == 'r') {
        stroke_cap_mode = SQUARE;
        strokeCap(SQUARE);
        console("SQUARE");
    }
    if (key == 'a') {
        // TODO WIP
        g->set_stroke_render_mode(STROKE_RENDER_MODE_TUBE_3D);
        console("STROKE_RENDER_MODE_TUBE_3D");
    }
    if (key == 's') {
        g->set_stroke_render_mode(STROKE_RENDER_MODE_LINE_SHADER);
        console("STROKE_RENDER_MODE_LINE_SHADER");
    }
    if (key == 'd') {
        g->set_stroke_render_mode(STROKE_RENDER_MODE_TRIANGULATE_2D);
        console("STROKE_RENDER_MODE_TRIANGULATE_2D");
    }
    if (key == 'f') {
        g->set_stroke_render_mode(STROKE_RENDER_MODE_NATIVE);
        console("STROKE_RENDER_MODE_NATIVE");
    }
}
