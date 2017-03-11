#pragma once

#include <vector>

#include "geometry.h"

class Boid {
public:
    Vec3 pos;
    Vec3 velocity;

    Vec3 forward; // x
    Vec3 up; // y
    Vec3 side; // z

    float max_speed;
    float max_accel; // Some fraction of max_speed

    std::vector<Vec3 (*)(Boid *)> behaviors;

    Boid() : pos(Vec3()), velocity(Vec3()), forward(Vec3(1.0, 0.0, 0.0)), up(Vec3(0.0, 1.0, 0.0)),
        side(Vec3(0.0, 0.0, 1.0)), max_speed(1.0), max_accel(0.1),
        behaviors(std::vector<Vec3 (*)(Boid *)>()) { }

    Boid fly(Vec3);
    Vec3 behave();
    Boid update();
    void draw();
};

class Flock {
public:
    std::vector<Boid> get_neighbors(Vec3, float);
    Flock update();
    void draw();
    std::vector<Boid> boids;

    Flock() : boids(std::vector<Boid>()) { }
};
