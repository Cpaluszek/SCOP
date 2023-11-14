#ifndef INC_MATH_H_
#define INC_MATH_H_

// Note: Vec2f useful?

#include "math/Mat4f.h"
#include "math/Vec3f.h"
#include "math/Vec2f.h"

namespace math {
    inline float radians(float degrees) {
        return degrees * 0.01745329251994329576923690768489f;
    }

    inline float lerp(float start, float end, float t) {
        return start + t * (end - start);
    }
}
#endif  // INC_MATH_H_
