#ifndef _INC_MATH_VEC2_H_
#define _INC_MATH_VEC2_H_

#include <ostream>
class Vec2f {
 public:

	 Vec2f();
	 Vec2f(float x, float y);

	 Vec2f operator+(const Vec2f &other) const;
	 Vec2f operator-(const Vec2f &other) const;

	 // Note: should be made static?
	 double length() const;
	 double sqrLength() const;
	 Vec2f scale(float scalar) const;
	 
	 // Note: should use double?
	 static float dot(const Vec2f& x, const Vec2f& y);
	 static Vec2f normalize(const Vec2f& src);

	friend std::ostream& operator<<(std::ostream& os, const Vec2f& src);

 private:
	 float x;
	 float y;
};

#endif	// _INC_MATH_VEC2_H_
