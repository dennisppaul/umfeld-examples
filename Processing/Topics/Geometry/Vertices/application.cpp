/**
 * Vertices 
 * by Simon Greenwold.
 * 
 * Draw a cylinder centered on the y-axis, going down 
 * from y=0 to y=height. The radius at the top can be 
 * different from the radius at the bottom, and the 
 * number of sides drawn is variable.
 */
#include "Umfeld.h"

using namespace umfeld;

void drawCylinder(float topRadius, float bottomRadius, float tall, int sides); //@diff(forward_declaration)

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {

}

void draw() {
    background(0.f); //@diff(color_range)
    lights(); //FIXME: lights() turns the shapes color into grey
    translate(width / 2, height / 2);
    rotateY(map(mouseX, 0, width, 0, PI));
    rotateZ(map(mouseY, 0, height, 0, -PI));
    noStroke();
    fill(1.f, 1.f, 1.f); //@diff(color_range)
    translate(0, -40, 0);
    drawCylinder(10, 180, 200, 16); // Draw a mix between a cylinder and a cone
                                    //drawCylinder(70, 70, 120, 64); // Draw a cylinder
                                    //drawCylinder(0, 180, 200, 4); // Draw a pyramid
}

void drawCylinder(float topRadius, float bottomRadius, float tall, int sides) {
    float angle          = 0;
    float angleIncrement = TWO_PI / sides;
    beginShape(QUAD_STRIP);
    for (int i = 0; i < sides + 1; ++i) {
        vertex(topRadius * cos(angle), 0, topRadius * sin(angle));
        vertex(bottomRadius * cos(angle), tall, bottomRadius * sin(angle));
        angle += angleIncrement;
    }
    endShape();

    // If it is not a cone, draw the circular top cap
    if (topRadius != 0) {
        angle = 0;
        beginShape(TRIANGLE_FAN);

        // Center point
        vertex(0, 0, 0);
        for (int i = 0; i < sides + 1; i++) {
            vertex(topRadius * cos(angle), 0, topRadius * sin(angle));
            angle += angleIncrement;
        }
        endShape();
    }

    // If it is not a cone, draw the circular bottom cap
    if (bottomRadius != 0) {
        angle = 0;
        beginShape(TRIANGLE_FAN);

        // Center point
        vertex(0, tall, 0);
        for (int i = 0; i < sides + 1; i++) {
            vertex(bottomRadius * cos(angle), tall, bottomRadius * sin(angle));
            angle += angleIncrement;
        }
        endShape();
    }
}