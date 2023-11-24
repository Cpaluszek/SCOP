#ifndef INC_CAMERA_H_
#define INC_CAMERA_H_

#include "./settings.h"
#include "./Window.h"
#include "./math.h"

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
