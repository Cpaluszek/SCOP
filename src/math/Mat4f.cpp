#include "../../inc/math/Mat4f.h"
#include <iostream>

Mat4f::Mat4f() {
	data.fill(0.0f);
}

// Initialize all the components on the matrix's diagonal
Mat4f::Mat4f(float value) {
	data.fill(0.0f);
	for (int i = 0; i < Mat4f::Size; i++) {
		data[i * (Mat4f::Size + 1)] = value;
	}
}

// | 1 0 0 x |
// | 0 1 0 y |
// | 0 0 1 z |
// | 0 0 0 1 |
Mat4f Mat4f::translate(Mat4f const& m, Vec3f const& translation) {
	Mat4f result(m);
	result.data[3 + Mat4f::Size * 0] = translation.x;
	result.data[3 + Mat4f::Size * 1] = translation.y;
	result.data[3 + Mat4f::Size * 2] = translation.z;
	return result;
}

// https://en.wikipedia.org/wiki/Rotation_matrix
// Angle in radians
// Note: what is Gimbal lock?
Mat4f Mat4f::rotate(Mat4f const& m, float angle, Vec3f const& axis) {
	float c = cos(angle);
	float s = sin(angle);
	Vec3f normalizedAxis = Vec3f::normalize(axis);

	Vec3f temp = normalizedAxis.scale(1.0f - c);	// axis(1 - cos(angle))

	// Get the rotation matrix
	Mat4f rot;
	rot.data[0] = c + temp.x * normalizedAxis.x;
	rot.data[1] = normalizedAxis.x * temp.y - normalizedAxis.z * s;
	rot.data[2] = normalizedAxis.z * temp.x + normalizedAxis.y * s;

	rot.data[4] = normalizedAxis.y * temp.x + normalizedAxis.z * s;
	rot.data[5] = c + normalizedAxis.y * temp.y;
	rot.data[6] = normalizedAxis.y * temp.z - normalizedAxis.x * s;

	rot.data[8] = normalizedAxis.z * temp.x - normalizedAxis.y * s;
	rot.data[9] = normalizedAxis.z * temp.y + normalizedAxis.x * s;
	rot.data[10] = c + normalizedAxis.z * temp.z;

	rot.data[15] = 1.0f;

	return m * rot;
}

Mat4f Mat4f::operator+(Mat4f const& other) const {
	Mat4f result;
	for (int i = 0; i < Mat4f::Size * Mat4f::Size; i++) {
		result.data[i] = this->data[i] + other.data[i];
	}
	return result;
}

Mat4f Mat4f::operator-(Mat4f const& other) const {
	Mat4f result;
	for (int i = 0; i < Mat4f::Size * Mat4f::Size; i++) {
		result.data[i] = this->data[i] - other.data[i];
	}
	return result;
}

Mat4f Mat4f::operator*(Mat4f const& other) const {
	Mat4f result;
	for (int i = 0; i < Mat4f::Size; i++) {
		for (int j = 0; j < Mat4f::Size; j++) {
			for (int k = 0; k < Mat4f::Size; k++) {
				result.data[i + j * Mat4f::Size] += this->data[i * Mat4f::Size + k] * other.data[i * Mat4f::Size + j];
			}
		}
	}
	return result;
}

std::ostream& operator<<(std::ostream& os, const Mat4f& src) {
	for (int i = 0; i < Mat4f::Size; i++) {
		os << "[";
		for (int j = 0; j < Mat4f::Size; j++) {
			os << src.data[i * Mat4f::Size + j] << "\t";
		}
		os << "]" << std::endl;
	}
	return os;
}
