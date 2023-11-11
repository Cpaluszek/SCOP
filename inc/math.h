#ifndef INC_MATH_H_
#define INC_MATH_H_

#include "math/Mat4f.h"
#include "math/Vec3f.h"
// Note: Vec2f useful?
#include "math/Vec2f.h"

// Todo: what is the best architecture for this function + math lib?
// use namespace?
inline float radians(float degrees) {
    return degrees * 0.01745329251994329576923690768489f;
}

#endif  // INC_MATH_H_
