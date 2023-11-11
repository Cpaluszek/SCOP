#ifndef INC_CAMERA_H_
#define INC_CAMERA_H_

#include "math.h"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
	public:
		Camera(Vec3f position = Vec3f(0.0f, 0.0f, 0.0f), Vec3f up = Vec3f(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

		Vec3f position;
		Vec3f Front;
		Vec3f Up;
		Vec3f Right;
		Vec3f WorldUp;

		float Yaw;
		float Pitch;
		float MovementSpeed;
		float Zoom;

		Mat4f GetViewMatrix() const;

	private:
		void updateCameraVectors();
};

#endif  // INC_CAMERA_H_
