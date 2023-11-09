#ifndef _INC_MATH_MAT4F_H_
#define _INC_MATH_MAT4F_H_

#include <array>
#include <ostream>

class Mat4f {
	public:
		static const int Size = 4;

		Mat4f();
		Mat4f(float value);

		friend std::ostream& operator<<(std::ostream& os, const Mat4f& src);
	private:
		std::array<float, 16> data;
};

#endif
