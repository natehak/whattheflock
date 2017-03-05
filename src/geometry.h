#pragma once

#include <tuple>

class Vec3 {
public:
    float x;
    float y;
    float z;

    Vec3(float, float, float);
    Vec3() : x(0.0), y(0.0), z(0.0) { }

    float length();
    Vec3 squared();
    Vec3 normalized();
    Vec3 cross(Vec3 vec);

    Vec3 operator-();
};

float operator*(Vec3 v1, Vec3 v2); // Dot product
Vec3 operator*(float scalar, Vec3 vec);

Vec3 operator+(Vec3 v1, Vec3 v2);
Vec3 operator-(Vec3 v1, Vec3 v2);
bool operator==(Vec3 v1, Vec3 v2);

