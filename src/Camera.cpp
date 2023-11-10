#include "../inc/Camera.h"

Camera::Camera(Vec3f position, Vec3f up, float yaw, float pitch)
	: Front(Vec3f(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), Zoom(ZOOM)
{
	this->position = position;
	this->WorldUp = up;
	this->Yaw = yaw;
	this->Pitch = pitch;
	updateCameraVectors();
}

Mat4f Camera::GetViewMatrix() const {
	return Mat4f::lookAt(this->position, this->position + this->Front, this->Up);
}

void Camera::updateCameraVectors() {
	Vec3f front;
	front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	front.y = sin(glm::radians(this->Pitch));
    front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    this->Front = Vec3f::normalize(front);
 
    this->Right = Vec3f::normalize(Vec3f::cross(this->Front, this->WorldUp));
    this->Up    = Vec3f::normalize(Vec3f::cross(this->Right, this->Front));
}
