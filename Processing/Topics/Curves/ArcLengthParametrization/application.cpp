/*
  Arc Length parametrization of curves by Jakub Valtar

  This example shows how to divide a curve into segments
  of an equal length and how to move along the curve with
  constant speed.

  To demonstrate the technique, a cubic Bézier curve is used.
  However, this technique is applicable to any kind of
  parametric curve.
*/
#include "Umfeld.h"
#include "BezierCurve.h"

using namespace umfeld;

BezierCurve curve;

std::vector<PVector> points;
std::vector<PVector> equidistantPoints;

float t     = 0.0;
float tStep = 0.004;

const int POINT_COUNT = 80; //@diff(const)

int borderSize = 40;

void curveStyle(); //@diff(forward_declaration)
void labelStyle(); //@diff(forward_declaration)
void circleStyle(); //@diff(forward_declaration)
void barBgStyle(); //@diff(forward_declaration)
void barStyle(); //@diff(forward_declaration)
void barLabelStyle(); //@diff(forward_declaration)

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {
    set_frame_rate(60); //@diff(frameRate)
    hint(ENABLE_SMOOTH_LINES); //@diff(available hints)
    textFont(loadFont("SourceCodePro-Regular.ttf", 16));
    textAlign(CENTER);
    textSize(16);
    strokeWeight(2);

    PVector aa(0,300);
    PVector bb(440, 0);
    PVector cc(-200, 0);
    PVector dd(240, 300);

    curve = BezierCurve(aa, bb, cc, dd);

    points            = curve.points(POINT_COUNT);
    equidistantPoints = curve.equidistantPoints(POINT_COUNT);
}


void draw() {

    // Show static value when mouse is pressed, animate otherwise
    if (isMousePressed) {
        int a = constrain(mouseX, (float)borderSize, width - borderSize);
        t     = map(a, borderSize, width - borderSize, 0.0, 1.0);
    } else {
        t += tStep;
        if (t > 1.0) {
            t = 0.0;
        }
    }

    background(1.f); //@diff(color_range)


    // draw curve and circle using standard parametrization
    pushMatrix();
    translate(borderSize, -50);

    labelStyle();
    text("STANDARD\nPARAMETRIZATION", 120, 310);

    curveStyle();
    beginShape(LINES);
    for (int i = 0; i < points.size() - 1; i += 2) {
        vertex(points[i].x, points[i].y);
        vertex(points[i + 1].x, points[i + 1].y);
    }
    endShape();

    circleStyle();
    PVector pos1 = curve.pointAtParameter(t);
    ellipse(pos1.x, pos1.y, 12, 12);

    popMatrix();


    // draw curve and circle using arc length parametrization
    pushMatrix();
    translate(width / 2 + borderSize, -50);

    labelStyle();
    text("ARC LENGTH\nPARAMETRIZATION", 120, 310);

    curveStyle();
    beginShape(LINES);
    for (int i = 0; i < equidistantPoints.size() - 1; i += 2) {
        vertex(equidistantPoints[i].x, equidistantPoints[i].y);
        vertex(equidistantPoints[i + 1].x, equidistantPoints[i + 1].y);
    }
    endShape();

    circleStyle();
    PVector pos2 = curve.pointAtFraction(t);
    ellipse(pos2.x, pos2.y, 12, 12);

    popMatrix();


    // draw seek bar
    pushMatrix();
    translate(borderSize, height - 45);

    int barLength = width - 2 * borderSize;

    barBgStyle();
    line(0, 0, barLength, 0);
    line(barLength, -5, barLength, 5);

    barStyle();
    line(0, -5, 0, 5);
    line(0, 0, t * barLength, 0);

    barLabelStyle();
    text(nf(t, 0, 2), barLength / 2, 25);
    popMatrix();
}


// Styles -----

void curveStyle() {
    stroke(.66f); //@diff(color_range)
    noFill();
}

void labelStyle() {
    noStroke();
    fill(.47f); //@diff(color_range)
}

void circleStyle() {
    noStroke();
    fill(0.f); //@diff(color_range)
}

void barBgStyle() {
    stroke(.86f); //@diff(color_range)
    noFill();
}

void barStyle() {
    stroke(.19f); //@diff(color_range)
    noFill();
}

void barLabelStyle() {
    noStroke();
    fill(.47f); //@diff(color_range)
}
