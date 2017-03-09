#include <tuple>

#include "boid.h"

Boid Boid::fly(Vec3 acceleration) {
    Boid b;
    Vec3 acc = acceleration.truncate(max_accel * max_speed);
    b.velocity = (velocity + acc).truncate(max_speed);
    b.pos = pos + b.velocity;

    // Reorient
    b.forward = b.velocity.normalized();
    Vec3 aprx_up = up; // Should be a weighted sum of acc, acc due to gravity, and the old up
    b.side = b.forward.cross(aprx_up);
    b.up = b.forward.cross(b.side);

    // Copy
    b.max_speed = max_speed;
    b.max_accel = max_accel;

    return b;
}

Vec3 Boid::behave() {
    // TODO: Implement steering accumulator
    return Vec3(0.0, 0.0, 0.0);
}

Boid Boid::update() {
    Vec3 acc = behave();
    return fly(acc);
}
