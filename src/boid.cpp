#include "boid.h"

void Boid::fly(Vec3 acceleration) {
    Vec3 acc = acceleration.truncate(max_accel * max_speed);
    velocity = (velocity + acc).truncate(max_speed);
    pos = pos + velocity;

    // Reorient
    forward = velocity.normalized();
    Vec3 aprx_up = up; // Should be a weighted sum of acc, acc due to gravity, and the old up
    side = forward.cross(aprx_up);
    up = forward.cross(side);
}

Vec3 Boid::behave() {
    // TODO: Implement steering accumulator
    return Vec3(0.0, 0.0, 0.0);
}

Boid Boid::update() {
    Vec3 acc = behave();
    fly(acc);
}
