#ifndef INC_CAMERA_H_
#define INC_CAMERA_H_

class Camera {
 public:
    Camera();

    // Vec3 position
    // Vec3 Front
    // Vec3 Up
    // Vec3 Right
    // Vec3 WorlUp

    float Yaw;
    float Pitch;
    float MovementSpeed;
    float Zoom;
};

#endif  // INC_CAMERA_H_
