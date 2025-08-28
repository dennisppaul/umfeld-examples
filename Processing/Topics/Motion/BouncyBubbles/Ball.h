#pragma once
#include "Umfeld.h"

using namespace umfeld;

#define numBalls 12

class Ball {
public:
    float x, y;
    float diameter;
    float vx = 0;
    float vy = 0;
    int   id;
    float spring   = 0.05;
    float gravity  = 0.03;
    float friction = -0.9;
    std::vector<Ball>* others; //@diff(pointer)

    Ball() = default;

    Ball(float xin, float yin, float din, int idin, std::vector<Ball>* oin) {
        x        = xin;
        y        = yin;
        diameter = din;
        id       = idin;
        others   = oin;
    }

    void collide() {
        for (int i = id + 1; i < numBalls; i++) {
            float dx       = others->at(i).x - x;
            float dy       = others->at(i).y - y;
            float distance = sqrt(dx * dx + dy * dy);
            float minDist  = others->at(i).diameter / 2 + diameter / 2;
            if (distance < minDist) {
                float angle   = atan2(dy, dx);
                float targetX = x + cos(angle) * minDist;
                float targetY = y + sin(angle) * minDist;
                float ax      = (targetX - others->at(i).x) * spring;
                float ay      = (targetY - others->at(i).y) * spring;
                vx -= ax;
                vy -= ay;
                others->at(i).vx += ax;
                others->at(i).vy += ay;
            }
        }
    }

    void move() {
        vy += gravity;
        x += vx;
        y += vy;
        if (x + diameter / 2 > width) {
            x = width - diameter / 2;
            vx *= friction;
        } else if (x - diameter / 2 < 0) {
            x = diameter / 2;
            vx *= friction;
        }
        if (y + diameter / 2 > height) {
            y = height - diameter / 2;
            vy *= friction;
        } else if (y - diameter / 2 < 0) {
            y = diameter / 2;
            vy *= friction;
        }
    }

    void display() {
        ellipse(x, y, diameter, diameter);
    }
};