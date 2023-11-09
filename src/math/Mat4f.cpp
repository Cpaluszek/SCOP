#include "../../inc/math/Mat4f.h"

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
