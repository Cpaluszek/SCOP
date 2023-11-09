#include <cmath>
#include "../../inc/math/Vec2f.h"

Vec2f::Vec2f(): x(0.0f), y(0.0f) {}

Vec2f::Vec2f(float value): x(value), y(value) {}

Vec2f::Vec2f(float x, float y): x(x), y(y) {}

Vec2f Vec2f::operator+(const Vec2f& other) const {
    return Vec2f(
            this->x + other.x,
            this->y + other.y);
}

Vec2f Vec2f::operator-(const Vec2f& other) const {
    return Vec2f(
            this->x - other.x,
            this->y - other.y);
}

Vec2f Vec2f::scale(float scalar) const {
    return Vec2f(this->x * scalar, this->y * scalar);
}

float Vec2f::length() const {
    return sqrt(this->x * this->x + this->y * this->y);
}

float Vec2f::sqrLength() const {
    return this->x * this->x + this->y * this->y;
}

void Vec2f::normalize() {
    float magnitude = this->length();
    if (magnitude == 0.0f) {
        return;
    }
    this->x /= magnitude;
    this->y /= magnitude;
}

// Static
float Vec2f::dot(const Vec2f& x, const Vec2f& y) {
    return x.x * y.x + x.y * y.y;
}

Vec2f Vec2f::normalize(const Vec2f& src) {
    float magnitude = src.length();
    if (magnitude == 0.0f) {
        return Vec2f(0.0f, 0.0f);
    }
    return Vec2f(src.x / magnitude, src.y / magnitude);
}

std::ostream& operator<<(std::ostream& os, const Vec2f& src) {
    os << "(" << src.x << "," << src.y << ")";
    return os;
}

