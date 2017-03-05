#include <cmath>

#include "types.h"

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) { }

Vec3 Vec3::cross(Vec3 vec) {
    return Vec3(((y * vec.z) - (z * vec.y)), ((z * vec.x) - (x * vec.z)), ((x * vec.y) - (y * vec.x)));
}

Vec3 Vec3::operator-() {
    return Vec3(-x, -y, -z);
}

float Vec3::length() {
    return sqrt((x * x) + (y * y) + (z * z));
}

Vec3 Vec3::normalized() {
    float len = length();
    return Vec3(x / len, y / len, z / len);
}

Vec3 Vec3::squared() {
    return Vec3(x * x, y * y, z * z);
}

float operator*(Vec3 v1, Vec3 v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Vec3 operator*(float scalar, Vec3 v) {
    return Vec3(scalar * v.x, scalar * v.y, scalar * v.z);
}

Vec3 operator+(Vec3 v1, Vec3 v2) {
    return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vec3 operator-(Vec3 v1, Vec3 v2) {
    return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

bool operator==(Vec3 v1, Vec3 v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}
