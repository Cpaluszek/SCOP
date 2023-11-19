#ifndef INC_CAMERA_H_
#define INC_CAMERA_H_

#include "./Window.h"
#include "./math.h"

const Vec3f START_POSITION = Vec3f(0.0f, 0.0f, 9.0f);
const Vec3f UP_DIR = Vec3f(0.0f, 1.0f, 0.0f);

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float ZOOM = 45.0f;

const float NEAR_CLIP = 0.1f;
const float FAR_CLIP = 100.0f;

class Camera {
 public:
     Camera(Vec3f position = START_POSITION, Vec3f up = UP_DIR,
             float yaw = YAW, float pitch = PITCH);

     Mat4f getViewMatrix() const;
     Mat4f getProjectionMatrix() const;

 private:
     Vec3f position;
     Vec3f front;
     Vec3f up;
     Vec3f right;
     Vec3f worldUp;

     float yaw;
     float pitch;
     float zoom;

     void updateCameraVectors();
};

#endif  // INC_CAMERA_H_
