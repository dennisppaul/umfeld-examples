#include "Umfeld.h"
#include "VertexBuffer.h"

using namespace umfeld;

int   stroke_join_mode = MITER;
int   stroke_cap_mode  = SQUARE;
float stroke_weight    = 30;
bool  close_shape      = false;

PImage*       umfeld_image;
PImage*       point_image;
VertexBuffer* mesh_shape;

void settings() {
    size(1024, 768);
    render_to_buffer = true;
}

void setup() {
    strokeJoin(stroke_join_mode);
    strokeCap(stroke_cap_mode);

    // hint(ENABLE_SMOOTH_LINES);
    g->stroke_properties(radians(10), radians(10), 179);
    g->set_stroke_render_mode(STROKE_RENDER_MODE_TRIANGULATE_2D);
    g->set_stroke_render_mode(STROKE_RENDER_MODE_TRIANGULATE_2D);

    umfeld_image = loadImage("umfeld.png");
    point_image  = loadImage("point.png");

    // TODO explain and test `render modes` ( default: `RENDER_MODE_SORTED_BY_Z_ORDER` or `RENDER_MODE_SORTED_BY_SUBMISSION_ORDER` )
    //      set_render_mode()
    //      hint(DISABLE_DEPTH_TEST); // add this as a reasonable default
    g->set_render_mode(RENDER_MODE_IMMEDIATELY);
    g->set_render_mode(RENDER_MODE_SORTED_BY_Z_ORDER);
    g->set_render_mode(RENDER_MODE_SORTED_BY_SUBMISSION_ORDER);

    g->set_stroke_render_mode(STROKE_RENDER_MODE_TRIANGULATE_2D);
    g->set_stroke_render_mode(STROKE_RENDER_MODE_NATIVE);

    g->set_point_render_mode(POINT_RENDER_MODE_TRIANGULATE);
    g->set_point_render_mode(POINT_RENDER_MODE_NATIVE);

    const std::vector<Vertex> vertices = loadOBJ("Panda.obj");
    mesh_shape                         = new VertexBuffer();
    mesh_shape->add_vertices(vertices);
}

void draw() {
    TRACE_FRAME;
    background(0.85f);

    constexpr bool ENABLE_DEBUG_TEXT         = false;
    constexpr bool ENABLE_CIRCLE_STROKE_FILL = false;
    constexpr bool ENABLE_CIRCLE_FILL        = false;
    constexpr bool ENABLE_CIRCLE_STROKE      = false;
    constexpr bool ENABLE_POLYGON            = true;
    constexpr bool ENABLE_POINTS             = true;
    constexpr bool ENABLE_LINE               = false;
    constexpr bool ENABLE_IMAGE              = false;
    constexpr bool ENABLE_LIGHT_SHAPES       = false;
    constexpr bool ENABLE_MESH               = false;
    constexpr bool ENABLE_TRANSPARENT_SHAPES = true;
    constexpr bool ENABLE_LINE_SHAPES        = true;
    constexpr bool ENABLE_FINAL_FLUSH        = false;

    if constexpr (ENABLE_DEBUG_TEXT) {
        TRACE_SCOPE_N("DEBUG_TEXT");
        fill(0);
        debug_text("FPS: " + nf(frameRate, 1), 10, 20);
        debug_text(to_string((g->get_render_mode() == RENDER_MODE_SORTED_BY_Z_ORDER) ? "RENDER_MODE_SORTED_BY_Z_ORDER" : (g->get_render_mode() == RENDER_MODE_SORTED_BY_SUBMISSION_ORDER ? "RENDER_MODE_SORTED_BY_SUBMISSION_ORDER" : "RENDER_MODE_IMMEDIATELY")), 10, 30);
    }
    if constexpr (ENABLE_CIRCLE_STROKE_FILL) {
        TRACE_SCOPE_N("CIRCLE_STROKE_FILL");
        strokeWeight(15);
        stroke(0.0f);
        fill(0.5f, 0.85f, 1.0f);
        circle(width / 2.0f, height / 2, mouseY);
        strokeWeight(stroke_weight);
    }
    if constexpr (ENABLE_CIRCLE_FILL) {
        TRACE_SCOPE_N("CIRCLE_FILL");
        noStroke();
        fill(0.5f, 0.85f, 1.0f);
        fill(0.85f);
        circle(width / 2.0f, height / 2, mouseY - 30);
    }
    if constexpr (ENABLE_CIRCLE_STROKE) {
        TRACE_SCOPE_N("CIRCLE_STROKE");
        strokeWeight(15);
        stroke(0.0f);
        noFill();
        circle(width / 2.0f, height / 2, mouseY - 60);
        strokeWeight(stroke_weight);
    }
    if constexpr (ENABLE_POLYGON) {
        TRACE_SCOPE_N("POLYGON");
        strokeWeight(stroke_weight);
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
    if constexpr (ENABLE_POINTS) {
        TRACE_SCOPE_N("POINTS");
        stroke(0.0f);
        noFill();
        pointSize(map(mouseX, 0, width, 1, 100));
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
    if constexpr (ENABLE_LINE) {
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
    if constexpr (ENABLE_IMAGE) {
        TRACE_SCOPE_N("IMAGE");
        fill(1, 0.5f);
        noStroke();
        pushMatrix();
        translate(width / 2, height * 0.5, mouseY - height / 2);
        rotate(frameCount * 0.0137f);
        translate(umfeld_image->width / -4, umfeld_image->height / -4);
        image(umfeld_image, 0, 0, umfeld_image->width / 2, umfeld_image->height / 2);
        popMatrix();
    }
    if constexpr (ENABLE_LIGHT_SHAPES) {
        TRACE_SCOPE_N("LIGHT_SHAPES");
        lights();
        fill(1);
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
    if constexpr (ENABLE_MESH) {
        TRACE_SCOPE_N("MESH");
        pushMatrix();
        translate(width * 0.5f, height * 0.75f);
        rotateX(PI);
        rotateY(PI);
        rotateX(sin(frameCount * 0.07f) * 0.07f);
        rotateY(sin(frameCount * 0.1f) * 0.1f);
        rotateZ(sin(frameCount * 0.083f) * 0.083f);
        scale(75);
        mesh(mesh_shape);
        pushMatrix();
        translate(2, 0);
        scale(0.4);
        rotateY(-0.7);
        mesh(mesh_shape);
        popMatrix();
        noStroke();
        fill(0.5f, 0.85f, 1.0f);
        pushMatrix();
        rotateX(HALF_PI);
        square(-3, -3, 6);
        popMatrix();
        popMatrix();
        if (isMousePressed) {
            mesh_shape->set_shape(LINES);
        } else {
            mesh_shape->set_shape(TRIANGLES);
        }
        if (isKeyPressed) {
            for (auto& v: mesh_shape->vertices_data()) {
                v.position.x += random(-0.02, 0.02);
                v.position.y += random(-0.02, 0.02);
                v.position.z += random(-0.02, 0.02);
            }
            mesh_shape->update();
        }
    }
    if constexpr (ENABLE_TRANSPARENT_SHAPES) {
        TRACE_SCOPE_N("TRANSPARENT_SHAPES");
        pushMatrix();

        translate(width * 0.5f, height * 0.75f);
        rotateX((mouseY * 0.1f) * 0.07f);
        rotateY((mouseX * 0.1f) * 0.1f);
        noStroke();

        translate(0, 0, -50);
        fill(1.0f, 0.0f, 0.0f, 0.5f);
        square(-100, -100, 200);

        translate(0, 0, 50);
        fill(0.0f, 1.0f, 0.0f, 0.5f);
        texture(umfeld_image);
        square(-100, -100, 200);
        texture();

        translate(0, 0, 50);
        fill(0.0f, 0.0f, 1.0f, 0.5f);
        square(-100, -100, 200);
        popMatrix();
    }
    if (ENABLE_LINE_SHAPES) {
        TRACE_SCOPE_N("LINE_SHAPES");
        noFill();
        stroke(0);
        strokeWeight(map(mouseY, 0, height, 1, 32));
        pushMatrix();
        translate(width / 2, height / 2);
        rotate(frameCount * 0.00137f);
        beginShape(TRIANGLE_FAN);
        vertex(0, 0);
        constexpr int N = 100;
        const float   R = height * 0.45f;
        for (int i = 0; i < N + 1; i++) {
            const float x = sin(i * TWO_PI / N) * R;
            const float y = cos(i * TWO_PI / N) * R;
            vertex(x, y);
        }
        endShape(CLOSE);
        popMatrix();
    }
    if constexpr (ENABLE_FINAL_FLUSH) {
        TRACE_SCOPE_N("FLUSH");
        flush();
    }
}

void mousePressed() {
    static bool toggle = false;
    if (toggle) {
        g->set_point_render_mode(POINT_RENDER_MODE_NATIVE);
        g->set_stroke_render_mode(STROKE_RENDER_MODE_NATIVE);
    } else {
        g->set_point_render_mode(POINT_RENDER_MODE_TRIANGULATE);
        g->set_stroke_render_mode(STROKE_RENDER_MODE_TRIANGULATE_2D);
    }
    toggle = !toggle;
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
