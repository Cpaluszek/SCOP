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


// x x x 0
// x x ? 0
// x ? x 0
// 0 0 0 0


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

    rot.data[15] = 1.0f;

    return m * rot;
}

Mat4f Mat4f::scale(const Mat4f& m, const Vec3f& factors) {
    Mat4f result(m);

    result.data[0] = m.data[0] * factors.x;
    result.data[5] = m.data[5] * factors.y;
    result.data[10] = m.data[10] * factors.z;

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
