#ifndef INC_MATH_H_
#define INC_MATH_H_

#include "math/Mat4f.h"
#include "math/Vec3f.h"

namespace math {
    inline float radians(const float degrees) {
        return degrees * 0.01745329251994329576923690768489f;
    }

    inline float lerp(const float start, const float end, const float t) {
        return start + t * (end - start);
    }
}
#endif  // INC_MATH_H_
