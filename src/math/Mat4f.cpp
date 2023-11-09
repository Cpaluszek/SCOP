#include "../../inc/math/Mat4f.h"
#include <ostream>

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

std::ostream& operator<<(std::ostream& os, const Mat4f& src) {
	for (int i = 0; i < Mat4f::Size; i++) {
		for (int j = 0; j < Mat4f::Size; j++) {
			os << src.data[i * Mat4f::Size + j] << "\t";
		}
		os << std::endl;
	}
	return os;
}
