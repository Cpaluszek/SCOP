#ifndef _INC_MATH_VEC3_H_
#define _INC_MATH_VEC3_H_

#include <ostream>
class Vec3f {
 public:

	 Vec3f();
	 Vec3f(float x, float y, float z);

	 Vec3f operator+(const Vec3f &other) const;
	 Vec3f operator-(const Vec3f &other) const;

	 // Note: should be made static?
	 double length() const;
	 double sqrLength() const;
	 Vec3f scale(float scalar) const;
	 
	 // Note: should use double?
	 static float dot(const Vec3f& x, const Vec3f& y);
	 static Vec3f cross(const Vec3f& x, const Vec3f y);
	 static Vec3f normalize(const Vec3f& src);

	friend std::ostream& operator<<(std::ostream& os, const Vec3f& src);

 private:
	 float x;
	 float y;
	 float z;
};

#endif	// _INC_MATH_VEC3_H_
