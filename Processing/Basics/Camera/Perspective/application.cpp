/**
 * Perspective. 
 * 
 * Move the mouse left and right to change the field of view (fov).
 * Click to modify the aspect ratio. The perspective() function
 * sets a perspective projection applying foreshortening, making 
 * distant objects appear smaller than closer ones. The parameters 
 * define a viewing volume with the shape of truncated pyramid. 
 * Objects near to the front of the volume appear their actual size, 
 * while farther objects appear smaller. This projection simulates 
 * the perspective of the world more accurately than orthographic projection. 
 * The version of perspective without parameters sets the default 
 * perspective and the version with four parameters allows the programmer 
 * to set the area precisely.
 */
#include "Umfeld.h" // @diff(include)

using namespace umfeld;

bool  showPerspective = false;
float aspect;


void settings() {
    size(640, 360);
}

void setup() {
    noStroke();
    fill(1.0f);              // @diff(color_range)
    hint(ENABLE_DEPTH_TEST); // @diff(available_hints)
}

void draw() {
    background(0.f); // @diff(color_range)
    lights();
    float cameraY = height / 2.f;
    float fov     = mouseX / width * PI / 2.f;
    float cameraZ = cameraY / tanf(fov / 2.f);


    perspective(fov, aspect, cameraZ / 10.f, cameraZ * 10.f); // FIXME: this disables the light

    translate(width / 2.f + 30.f, height / 2.f, 0.f);
    rotateX(-PI / 6.f);
    rotateY(PI / 3.f + mouseY / height * PI);
    box(45.f);
    translate(0.f, 0.f, -50.f);
    box(30.f);

    noLights();
}

void mousePressed() {
    aspect = aspect / 2.f;
}
void mouseReleased() {
    aspect = width / height;
}

/*
note:
- `pespective()` and `ortho()` disables the `lights()`.
*/
