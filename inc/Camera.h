#ifndef INC_CAMERA_H_
#define INC_CAMERA_H_

#include "settings.h"
#include "Window.h"
#include "math.h"

enum Camera_Input {
    ZOOM_IN,
    ZOOM_OUT
};

class Camera {
 public:
     explicit Camera(Vec3f position);

     Mat4f getViewMatrix() const;
     Mat4f getProjectionMatrix() const;

     void processKeyboardInput(Camera_Input input, float deltaTime);

 private:
     Mat4f view;
     Mat4f projection;

     Vec3f position;
     Vec3f worldUp = UP_DIR;
     Vec3f front;
     Vec3f up;
     Vec3f right;

     float yaw = YAW;
     float pitch= PITCH;
     float zoom = ZOOM;

     void updateCameraVectors();
};

#endif  // INC_CAMERA_H_
