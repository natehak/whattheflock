#pragma once

#include "geometry.h"

class Boid {
public:
    Vec3 pos;
    float max_speed;
    float speed;
    float max_accel; // Some fraction of max_speed
    Rotation orientation;

    Boid(): pos(Vec3()), max_speed(100.0), speed(0.0), max_accel(0.25), orientation(Rotation()) { }

    Boid update();
};
