#include "../inc/Camera.h"

// Todo: remove parameters
Camera::Camera(const Vec3f position, const Vec3f up, const float yaw, const float pitch)
    : front(Vec3f(0.0f, 0.0f, -1.0f)), zoom(ZOOM) {
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

Mat4f Camera::getViewMatrix() const {
    return Mat4f::lookAt(this->position, this->position + this->front, this->up);
}

Mat4f Camera::getProjectionMatrix() const {
    return Mat4f::perspective(math::radians(this->zoom),
            ASPECT_RATIO, NEAR_CLIP, FAR_CLIP);
}

void Camera::updateCameraVectors() {
    Vec3f front;
    front.x = cos(math::radians(this->yaw)) * cos(math::radians(this->pitch));
    front.y = sin(math::radians(this->pitch));
    front.z = sin(math::radians(this->yaw)) * cos(math::radians(this->pitch));
    this->front = Vec3f::normalize(front);

    this->right = Vec3f::normalize(Vec3f::cross(this->front, this->worldUp));
    this->up    = Vec3f::normalize(Vec3f::cross(this->right, this->front));
}

