#pragma once
#include "Umfeld.h"
#include "PVector.h"
#include "Particle.h"

using namespace umfeld;

/*
 * C++ Inheritance Syntax vs Java:
 * 
 * Java: class CrazyParticle extends Particle
 * C++:  class CrazyParticle : public Particle
 * 
 * Key differences in method calls:
 * 1. Constructor chaining:
 *    Java: super(l);
 *    C++:  : Particle(l) { ... } (initialization list)
 * 
 * 2. Parent method calls:
 *    Java: super.update();
 *    C++:  Particle::update(); (scope resolution operator)
 * 
 * 3. Method overriding:
 *    Java: @Override (annotation, optional)
 *    C++:  override (keyword, recommended for safety)
 * 
 * The 'override' keyword helps catch errors if the base class method
 * signature doesn't match what we think we're overriding.
 */

// A subclass of Particle

class CrazyParticle : public Particle {
public:
    // Just adding one new variable to a CrazyParticle
    // It inherits all other fields from "Particle", and we don't have to retype them!
    float theta;

    // The CrazyParticle constructor can call the parent class (super class) constructor
    CrazyParticle(PVector l) : Particle(l) {
        // In C++, we use initialization list to call parent constructor
        // One more line of code to deal with the new variable, theta
        theta = 0.0;
    }

    virtual ~CrazyParticle() {} // Virtual destructor

    // Notice we don't have the method run() here; it is inherited from Particle

    // This update() method overrides the parent class update() method
    void update() override {
        Particle::update(); // Call parent class update method
        // Increment rotation based on horizontal velocity
        float theta_vel = (velocity.x * velocity.mag()) / 10.0f;
        theta += theta_vel;
    }

    // This display() method overrides the parent class display() method
    void display() override {
        // Render the ellipse just like in a regular particle
        Particle::display(); // Call parent class display method
        // Then add a rotating line
        pushMatrix();
        translate(position.x, position.y);
        rotate(theta);
        stroke(1.f, lifespan/255.f); //@diff(color_range)
        line(0, 0, 25, 0);
        popMatrix();
    }
};