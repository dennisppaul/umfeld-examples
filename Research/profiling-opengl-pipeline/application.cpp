#include "Umfeld.h"

using namespace umfeld;

int   stroke_join_mode = MITER;
int   stroke_cap_mode  = SQUARE;
float stroke_weight    = 30;
bool  close_shape      = false;

PImage* umfeld_image;
PImage* point_image;

void settings() {
    size(1024, 768);
    render_to_buffer = true;
}

void setup() {
    strokeJoin(stroke_join_mode);
    strokeCap(stroke_cap_mode);
    strokeWeight(stroke_weight);

    // hint(ENABLE_SMOOTH_LINES);
    g->stroke_properties(radians(10), radians(10), 179);
    g->set_stroke_render_mode(STROKE_RENDER_MODE_TRIANGULATE_2D);

    umfeld_image = loadImage("umfeld.png");
    point_image  = loadImage("point.png");

    // TODO explain and test `render modes` ( default: `RENDER_MODE_SORTED_BY_Z_ORDER` or `RENDER_MODE_SORTED_BY_SUBMISSION_ORDER` )
    //      set_render_mode()
    //      hint(DISABLE_DEPTH_TEST); // add this as a reasonable default
    g->set_render_mode(RENDER_MODE_IMMEDIATELY);
    g->set_render_mode(RENDER_MODE_SORTED_BY_Z_ORDER);
    g->set_render_mode(RENDER_MODE_SORTED_BY_SUBMISSION_ORDER);

    hint(ENABLE_DEPTH_TEST); // enable depth testing for 3D rendering

    g->set_point_render_mode(POINT_RENDER_MODE_TRIANGULATE);
    pointSize(32);
}

void draw() {
    TRACE_FRAME;
    background(0.85f);

    fill(0);
    debug_text("FPS: " + std::to_string(frameRate), 10, 20);

    {
        TRACE_SCOPE_N("CIRCLE_STROKE_FILL");
        strokeWeight(15);
        stroke(0.0f);
        fill(0.5f, 0.85f, 1.0f);
        circle(width / 2.0f, height / 2, mouseY);
        strokeWeight(stroke_weight);
    }
    {
        TRACE_SCOPE_N("CIRCLE_FILL");
        noStroke();
        fill(0.5f, 0.85f, 1.0f);
        fill(0.85f);
        circle(width / 2.0f, height / 2, mouseY - 30);
    }
    {
        TRACE_SCOPE_N("CIRCLE_STROKE");
        strokeWeight(15);
        stroke(0.0f);
        noFill();
        circle(width / 2.0f, height / 2, mouseY - 60);
        strokeWeight(stroke_weight);
    }
    {
        TRACE_SCOPE_N("POLYGON");
        stroke(0.0f);
        fill(0.5f, 0.85f, 1.0f);
        beginShape(POLYGON);
        vertex(412, 204);
        vertex(522, 204);
        vertex(mouseX, mouseY);
        vertex(632, 314);
        vertex(632, 424);
        vertex(412, 424);
        vertex(312, 314);
        endShape(close_shape);
    }
    {
        TRACE_SCOPE_N("POINTS");
        stroke(0.0f);
        noFill();
        texture(point_image);
        beginShape(POINTS);
        for (int i = 0; i < 32; i++) {
            const float r = TWO_PI * (frameCount + i * sin((frameCount - i) * 0.0537)) * ((i + 32) * 0.0137f) / 360.0f;
            const float x = sin(r) * 300 + width / 2;
            const float y = cos(r) * 300 + height / 2;
            vertex(x, y);
        }
        endShape();
        texture();
    }
    {
        TRACE_SCOPE_N("LINE");
        noFill();
        stroke(1.0f, 0.25f, 0.35f, 0.5f);
        line(width / 2.0f - 30, height / 2 - 100,
             width / 2.0f + 30, height / 2 - 40);
        stroke(1.0f, 0.25f, 0.35f, 0.5f);
        beginShape(LINES);
        vertex(mouseX, mouseY);
        vertex(width / 2.0f + 30, height / 2 - 100);
        endShape();
    }
    {
        TRACE_SCOPE_N("IMAGE");
        fill(1);
        noStroke();
        pushMatrix();
        translate(mouseX, mouseY);
        rotate(frameCount * 0.0137f);
        translate(umfeld_image->width / -4, umfeld_image->height / -4);
        image(umfeld_image, 0, 0, umfeld_image->width / 2, umfeld_image->height / 2);
        popMatrix();
    }
    {
        // flush();

        TRACE_SCOPE_N("LIGHT_SHAPES");
        lights();

        pushMatrix();
        translate(width / 2 - 120, height / 2, 0);
        sphere(120);
        popMatrix();

        pushMatrix();
        translate(width / 2 + 120, height / 2, 0);
        sphere(120);
        popMatrix();

        noLights();
    }
    {
        TRACE_SCOPE_N("FLUSH");
        flush();
    }
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
        g->set_stroke_render_mode(STROKE_RENDER_MODE_NATIVE);
        console("STROKE_RENDER_MODE_NATIVE");
    }
    if (key == 's') {
        g->set_stroke_render_mode(STROKE_RENDER_MODE_TRIANGULATE_2D);
        console("STROKE_RENDER_MODE_TRIANGULATE_2D");
    }
    if (key == 'd') {
        g->set_stroke_render_mode(STROKE_RENDER_MODE_TUBE_3D);
        console("STROKE_RENDER_MODE_TUBE_3D");
    }
    if (key == 'f') {
        g->set_stroke_render_mode(STROKE_RENDER_MODE_LINE_SHADER);
        console("STROKE_RENDER_MODE_LINE_SHADER");
    }
    if (key == ' ') {
        close_shape = !close_shape;
    }
}
