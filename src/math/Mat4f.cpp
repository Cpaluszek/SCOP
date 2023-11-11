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

// https://en.wikipedia.org/wiki/Rotation_matrix
// Angle in radians
// Note: what is Gimbal lock?
// Todo: optimize
Mat4f Mat4f::rotate(Mat4f const& m, float angle, Vec3f const& axis) {
    float c = cos(angle);
    float s = sin(angle);
    Vec3f normalizedAxis = Vec3f::normalize(axis);

    Vec3f temp = normalizedAxis.scale(1.0f - c);	// axis(1 - cos(angle))

    // Get the rotation matrix
    Mat4f rot;
    rot.data[0] = c + temp.x * normalizedAxis.x;
    rot.data[1] = temp.x * normalizedAxis.y + normalizedAxis.z * s;
    rot.data[2] = temp.x * normalizedAxis.z - normalizedAxis.y * s;

    rot.data[4] = temp.y * normalizedAxis.x - normalizedAxis.z * s;
    rot.data[5] = c + temp.y * normalizedAxis.y;
    rot.data[6] = temp.y * normalizedAxis.z + normalizedAxis.x * s;

    rot.data[8] = temp.z * normalizedAxis.x + normalizedAxis.y * s;
    rot.data[9] = temp.z * normalizedAxis.y - normalizedAxis.x * s;
    rot.data[10] = c + temp.z * normalizedAxis.z;

    Mat4f result = m * rot;
    result.data[3] = m.data[3];
    result.data[7] = m.data[7];
    result.data[11] = m.data[11];
    result.data[15] = m.data[15];
    return result;
}

Mat4f Mat4f::scale(const Mat4f& m, const Vec3f& factors) {
    Mat4f result(m);

    result.data[0] = m.data[0] * factors.x;
    result.data[5] = m.data[5] * factors.y;
    result.data[10] = m.data[10] * factors.z;

    return result;
}


Mat4f Mat4f::perspective(float fov, float aspect, float near, float far) {
    Mat4f result;

    float invTanHalfFov = 1.0f / tan(fov / 2.0f);

    result.data[0] = invTanHalfFov / aspect;
    result.data[5] = invTanHalfFov;
    result.data[10] = - (far + near) / (far - near);
    result.data[14] = - 1.0f;
    result.data[11] = - (2.0f * far * near) / (far - near);
    return result;
}

Mat4f Mat4f::lookAt(Vec3f const& eye, Vec3f const& center, Vec3f const& up) {
    Vec3f const f(Vec3f::normalize(center - eye)); 
    Vec3f const s(Vec3f::normalize(Vec3f::cross(f, up))); 
    Vec3f const u(Vec3f::cross(s, f)); 

    Mat4f result(1.0f);

    result.data[0] = s.x;
    result.data[1] = s.y;
    result.data[2] = s.z;

    result.data[4] = u.x;
    result.data[5] = u.y;
    result.data[6] = u.z;

    result.data[8] = -f.x;
    result.data[9] = -f.y;
    result.data[10] = -f.z;

    result.data[3] = -Vec3f::dot(s, eye);
    result.data[7] = -Vec3f::dot(u, eye);
    result.data[11] = Vec3f::dot(f, eye);

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
                result.data[i + j * Mat4f::Size] += this->data[i * Mat4f::Size + k] * other.data[k * Mat4f::Size + j];
            }
        }
    }
    return result;
}

float& Mat4f::operator[](int index) {
	if (index >= Mat4f::Size) {
		std::cout << "Array index out of bounds" << std::endl;
		exit(0);
	}
	return data[index];
}

std::ostream& operator<<(std::ostream& os, const Mat4f& src) {
    os << std::fixed << std::setprecision(6) << "mat4x4(";
    for (int i = 0; i < Mat4f::Size; i++) {
        os << "(";
        for (int j = 0; j < Mat4f::Size; j++) {
            os << src.data[j * Mat4f::Size + i];
            if (j < Mat4f::Size - 1) {
                os << ", ";
            }
        }
        os << ")";
        if (i < Mat4f::Size - 1) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}

// Note: test
Mat4f Mat4f::transpose(Mat4f const& m) {
    Mat4f result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.data[i * 4 + j] = m.data[j * 4 + i];
        }
    }
    return result;
}
