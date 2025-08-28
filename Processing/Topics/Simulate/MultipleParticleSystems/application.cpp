/**
 * Multiple Particle Systems
 *
 * Click the mouse to generate a burst of particles
 * at mouse position.
 *
 * Each burst is one instance of a particle system
 * with Particles and CrazyParticles (a subclass of Particle). 
 * Note use of Inheritance and Polymorphism.
 */

#include "Umfeld.h"
#include "ParticleSystem.h"

using namespace umfeld;

std::vector<ParticleSystem> systems; //@diff(std::vector)

void settings() {
    size(640, 360);
}

void setup() {
    textFont(loadFont("SourceCodePro-Regular.ttf", 15));
    systems = std::vector<ParticleSystem>();
}

void draw() {
    background(0.f); //@diff(color_range)
    for (ParticleSystem& ps: systems) {
        ps.run();
        ps.addParticle();
    }
    if (systems.empty()) {
        fill(1.f); //@diff(color_range)
        textAlign(CENTER);
        noStroke();
        text("click mouse to add particle systems", width / 2, height / 2);
        stroke(1.f);
    }
}

void mousePressed() {
    systems.push_back(ParticleSystem(1, PVector(mouseX, mouseY)));
}