#ifndef INC_CAMERA_H_
#define INC_CAMERA_H_

#include "./math.h"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

const float NEAR_CLIP = 0.1f;
const float FAR_CLIP = 100.0f;

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    RIGHT,
    LEFT
};

class Camera {
 public:
     Camera(Vec3f position = Vec3f(0.0f, 0.0f, 0.0f), Vec3f up = Vec3f(0.0f, 1.0f, 0.0f),
             float yaw = YAW, float pitch = PITCH);

     Vec3f position;
     Vec3f front;
     Vec3f up;
     Vec3f right;
     Vec3f worldUp;

     float yaw;
     float pitch;
     float movementSpeed;
     float zoom;

     Mat4f getViewMatrix() const;
     void processKeyboardInput(Camera_Movement direction, float delta_time);

 private:
     void updateCameraVectors();
};

#endif  // INC_CAMERA_H_
