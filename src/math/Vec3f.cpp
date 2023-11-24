#include <cmath>
#include "../../inc/math/Vec3f.h"

Vec3f::Vec3f(): x(0.0f), y(0.0f), z(0.0f) {}

Vec3f::Vec3f(float value): x(value), y(value), z(value) {}

Vec3f::Vec3f(float x, float y, float z): x(x), y(y), z(z) {}

Vec3f Vec3f::operator+(const Vec3f& other) const {
    return {
            this->x + other.x,
            this->y + other.y,
            this->z + other.z};
}

Vec3f Vec3f::operator+=(const Vec3f& other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

Vec3f Vec3f::operator-(const Vec3f& other) const {
    return {
            this->x - other.x,
            this->y - other.y,
            this->z - other.z};
}

Vec3f Vec3f::operator-=(const Vec3f& other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

Vec3f Vec3f::operator*(float value) const {
    return this->scale(value);
}

Vec3f Vec3f::scale(float scalar) const {
    return {this->x * scalar, this->y * scalar, this->z * scalar};
}

float Vec3f::length() const {
    return static_cast<float>(sqrtf(this->x * this->x + this->y * this->y + this->z * this->z));
}

float Vec3f::sqrLength() const {
    return this->x * this->x + this->y * this->y + this->z * this->z;
}

void Vec3f::normalize() {
    float magnitude = this->length();
    if (magnitude == 0.0f) {
        return;
    }
    this->x /= magnitude;
    this->y /= magnitude;
    this->z /= magnitude;
}

// Static
float Vec3f::dot(const Vec3f& x, const Vec3f& y) {
    return x.x * y.x + x.y * y.y + x.z * y.z;
}

Vec3f Vec3f::cross(const Vec3f &x, const Vec3f& y) {
    return {
            x.y * y.z - x.z * y.y,
            x.z * y.x - x.x * y.z,
            x.x * y.y - x.y * y.x};
}

Vec3f Vec3f::normalize(const Vec3f& src) {
    float magnitude = src.length();
    if (magnitude == 0.0f) {
        return {0.0f, 0.0f, 0.0f};
    }
    return {src.x / magnitude, src.y / magnitude, src.z / magnitude};
}

std::ostream& operator<<(std::ostream& os, const Vec3f& src) {
    os << "(" << src.x << "," << src.y << "," << src.z << ")";
    return os;
}

