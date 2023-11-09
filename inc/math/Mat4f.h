#ifndef _INC_MATH_MAT4F_H_
#define _INC_MATH_MAT4F_H_

#include <array>
#include <ostream>
#include <cmath>
#include "Vec3f.h"

class Mat4f {
	public:
		static const int Size = 4;

		Mat4f();
		Mat4f(float value);

		static Mat4f translate(Mat4f const& m, Vec3f const& translation);
		// Todo: rotate
		static Mat4f rotate(Mat4f const& m, float angle, Vec3f const& axis);
		// Todo: scale
		static Mat4f scale(Mat4f const& m, Vec3f const& factors);

		// Todo: frustum
		// Todo: ortho 
		// Todo: lookAt
		// Todo: perspective
		// Todo: project
		
		Mat4f operator+(Mat4f const& other) const;
		Mat4f operator-(Mat4f const& other) const;
		Mat4f operator*(Mat4f const& other) const;

		friend std::ostream& operator<<(std::ostream& os, const Mat4f& src);
	private:
		std::array<float, 16> data;
};

#endif
