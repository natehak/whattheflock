#pragma once

#include "geometry.h"

class Boid {
public:
    Vec3 pos;
    Vec3 velocity;

    Vec3 forward;
    Vec3 up;
    Vec3 side;

    float max_speed;
    float max_accel; // Some fraction of max_speed

    Boid(): pos(Vec3()), velocity(Vec3()), forward(Vec3(0.0, 0.0, 1.0)), up(Vec3(0.0, 1.0, 0.0)),
        side(Vec3(1.0, 0.0, 0.0)), max_speed(100.0), max_accel(0.25) { }

    Boid fly(Vec3);
    Vec3 behave();
    Boid update();
};
