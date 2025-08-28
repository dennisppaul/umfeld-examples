/**
 * Gravitational Attraction (3D) 
 * by Daniel Shiffman.  
 * 
 * Simulating gravitational attraction 
 * G ---> universal gravitational constant
 * m1 --> mass of object #1
 * m2 --> mass of object #2
 * d ---> distance between objects
 * F = (G*m1*m2)/(d*d)
 *
 * For the basics of working with PVector, see
 * http://processing.org/learning/pvector/
 * as well as examples in Topics/Vectors/
 * 
 */
#include "Umfeld.h"
#include "Sun.h"
#include "Planet.h"

using namespace umfeld;

// A bunch of planets
std::vector<Planet> planets(10); //@diff(std::vector)
// One sun (note sun is not attracted to planets (violation of Newton's 3rd Law)
Sun s;

// An angle to rotate around the scene
float angle = 0;

void settings() {
    size(640, 360, RENDERER_OPENGL_3_3_CORE); //@diff(renderer)
}

void setup() {

    // Some random planets
    for (int i = 0; i < planets.size(); i++) {
        planets[i] = Planet(random(0.1, 2), random(-width / 2, width / 2), random(-height / 2, height / 2), random(-100, 100));
    }
    // A single sun
    s = Sun();
}

void draw() {
    background(0.f); //@diff(color_range)
    // Setup the scene
    sphereDetail(8);
    lights();
    translate(width / 2, height / 2);
    rotateY(angle);


    // Display the Sun
    s.display();

    // All the Planets
    for (Planet& planet: planets) {
        // Sun attracts Planets
        PVector force = s.attract(planet);
        planet.applyForce(force);
        // Update and draw Planets
        planet.update();
        planet.display();
    }

    // Rotate around the scene
    angle += 0.003;
}