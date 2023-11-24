#include "../inc/Camera.h"

Camera::Camera(const Vec3f position) {
    this->position = position;
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
    Vec3f newFront(
        cosf(math::radians(this->yaw)) * cosf(math::radians(this->pitch)),
        sinf(math::radians(this->pitch)),
        sinf(math::radians(this->yaw)) * cosf(math::radians(this->pitch))
    );
    this->front = Vec3f::normalize(newFront);

    this->right = Vec3f::normalize(Vec3f::cross(this->front, this->worldUp));
    this->up    = Vec3f::normalize(Vec3f::cross(this->right, this->front));
}

