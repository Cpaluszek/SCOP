#ifndef INC_MATH_VEC3F_H_
#define INC_MATH_VEC3F_H_

#include <ostream>


class Vec3f {
 public:
    float x;
    float y;
    float z;

    Vec3f();
    explicit Vec3f(float value);
    Vec3f(float x, float y, float z);

    Vec3f operator+(const Vec3f &other) const;
    Vec3f operator-(const Vec3f &other) const;

    // Note: should be made static?
    float length() const;
    float sqrLength() const;
    Vec3f scale(float scalar) const;
    void normalize();

    static float dot(const Vec3f& x, const Vec3f& y);
    static Vec3f cross(const Vec3f& x, const Vec3f y);
    static Vec3f normalize(const Vec3f& src);
};

std::ostream& operator<<(std::ostream& os, const Vec3f& src);

#endif  // INC_MATH_VEC3F_H_
