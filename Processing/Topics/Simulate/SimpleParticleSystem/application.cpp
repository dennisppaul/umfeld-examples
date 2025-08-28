/**
 * Simple Particle System
 * by Daniel Shiffman.  
 * 
 * Particles are generated each cycle through draw(),
 * fall with gravity, and fade out over time.
 * A ParticleSystem object manages a variable size (ArrayList) 
 * list of particles. 
 */
#include "Umfeld.h"
#include "PVector.h"
#include "ParticleSystem.h"

using namespace umfeld;

ParticleSystem ps;

void settings() {
    size(640, 360);
}

void setup() {
    ps = ParticleSystem(PVector(width / 2, 50));
}

void draw() {
    background(0.f); //@diff(color_range)
    ps.addParticle();
    ps.run();
}