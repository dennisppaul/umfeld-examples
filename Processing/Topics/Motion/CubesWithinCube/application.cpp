/**
 * Cubes Contained Within a Cube 
 * by Ira Greenberg.  
 * 
 * Collision detection against all
 * outer cube's surfaces. 
 */
#include "Umfeld.h"
#include "Cube.h"

using namespace umfeld;

// 20 little internal cubes
std::vector<Cube> cubies(20);

// Size of outer cube
void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {
    for (int i = 0; i < cubies.size(); i++) {
        // Cubies are randomly sized
        float cubieSize = random(5, 15);
        cubies[i] = Cube(cubieSize, cubieSize, cubieSize);
    }
}

void draw() {
    background(.19f); //@diff(color_range)
    lights(); //FIXME: this turns the object into grey(no lighting)

    // Center in display window
    translate(width / 2, height / 2, -130);

    // Rotate everything, including external large cube
    rotateX(frameCount * 0.001);
    rotateY(frameCount * 0.002);
    rotateZ(frameCount * 0.001);
    stroke(1.f); //@diff(color_range)


    // Outer transparent cube, just using box() method
    noFill();
    box(bounds);

    // Move and rotate cubies
    for (Cube& c: cubies) {
        c.update();
        c.display();
    }
}
