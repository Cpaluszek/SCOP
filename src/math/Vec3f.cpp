#include <cmath>
#include "../../inc/math/Vec3f.h"

Vec3f::Vec3f(): x(0.0f), y(0.0f), z(0.0f) {}

Vec3f::Vec3f(float x, float y, float z): x(x), y(y), z(z) {}

Vec3f Vec3f::operator+(const Vec3f& other) const {
	return Vec3f(
			this->x + other.x,
			this->y + other.y,
			this->z + other.z
		);
}

Vec3f Vec3f::operator-(const Vec3f& other) const {
	return Vec3f(
			this->x - other.x,
			this->y - other.y,
			this->z - other.z
		);
}

double Vec3f::length() const {
	return 	sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

double Vec3f::sqrLength() const {
	return 	this->x * this->x + this->y * this->y + this->z * this->z;
}

// Static
float Vec3f::dot(const Vec3f& x, const Vec3f& y) {
	return x.x * y.x + x.y * y.y + x.z * y.z;
}

 Vec3f Vec3f::cross(const Vec3f &x, const Vec3f y) {
	return Vec3f(
			x.y * y.z - x.z * y.y,
			x.z * y.x - x.x * y.z,
			x.x * y.y - x.y * y.x 
	);
}

Vec3f Vec3f::normalize(const Vec3f& src) {
	float magnitude = src.length();
	if (magnitude == 0.0f) {
		return Vec3f(0.0f, 0.0f, 0.0f);
	}
	return Vec3f(src.x / magnitude, src.y / magnitude, src.z / magnitude);
}

std::ostream& operator<<(std::ostream& os, const Vec3f& src) {
	os << "(" << src.x << "," << src.y << "," << src.z << ")";
	return os;
}

