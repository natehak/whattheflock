#include <GLFW/glfw3.h>

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
    b.behaviors = behaviors;

    return b;
}

Vec3 Boid::behave() {

    Vec3 accel = Vec3(0.0, 0.0, 0.0);

    for (Vec3 (*behavior)(Boid *) : behaviors) {
        accel = accel + behavior(this);
    }

    return accel;
}

Boid Boid::update() {
    Vec3 acc = behave();
    return fly(acc);
}

void Boid::draw() {
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);
    float tf[] = {forward.x, forward.y, forward.z, 0,
                  up.x, up.y, up.z, 0,
                  side.x, side.y, side.z, 0,
                  pos.x, pos.y, pos.z, 1};
    glMultMatrixf(tf);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);
        float tip = velocity.length();
        glVertex3f(tip, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.5f);
        glVertex3f(0.0f, 0.5f, -0.5f);

        glVertex3f(tip, 0.0f, 0.0f);
        glVertex3f(0.0f, -0.5f, 0.5f);
        glVertex3f(0.0f, 0.5f, 0.5f);

        glVertex3f(tip, 0.0f, 0.0f);
        glVertex3f(0.0f, -0.5f, 0.5f);
        glVertex3f(0.0f, -0.5f, -0.5f);

        glVertex3f(tip, 0.0f, 0.0f);
        glVertex3f(0.0f, -0.5f, -0.5f);
        glVertex3f(0.0f, 0.5f, -0.5f);

        glVertex3f(0.0f, 0.5f, -0.5f);
        glVertex3f(0.0f, 0.5f, 0.5f);
        glVertex3f(0.0f, -0.5f, 0.5f);

        glVertex3f(0.0f, 0.5f, -0.5f);
        glVertex3f(0.0f, -0.5f, 0.5f);
        glVertex3f(0.0f, -0.5f, -0.5f);

    glEnd();
    glPopMatrix();

}

Flock Flock::update() {
    Flock f;
    for (Boid b : boids) {
        f.boids.push_back(b.update());
    }
    return f;
}

std::vector<Boid> Flock::get_neighbors(Vec3 pos, float radius) {
    std::vector<Boid> neighbors;
    for (Boid b : boids) {
        if (pos.dist(b.pos) < radius) {
            neighbors.push_back(b);
        }
    }
    return neighbors;
}

void Flock::draw() {
    for (Boid b : boids) {
        b.draw();
    }
}
