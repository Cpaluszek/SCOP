#include "Camera.h"
#include <algorithm>

Camera::Camera(const Vec3f position) {
    this->position = position;
    updateCameraVectors();
    this->projection = Mat4f::perspective(math::radians(this->zoom), 
            ASPECT_RATIO, NEAR_CLIP, FAR_CLIP);
}

Mat4f Camera::getViewMatrix() const {
    return this->view;
}

Mat4f Camera::getProjectionMatrix() const {
    return this->projection;
}

void Camera::processKeyboardInput(Camera_Input input, float deltaTime) {
    if (input == ZOOM_IN) {
        this->zoom -= ZOOM_SPEED * deltaTime;
    } else if (input == ZOOM_OUT) {
        this->zoom += ZOOM_SPEED * deltaTime;
    }
    // Clamp
    this->zoom = std::max(1.0f, this->zoom);
    this->zoom = std::min(45.0f, this->zoom);

    this->projection = Mat4f::perspective(
            math::radians(this->zoom), 
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

    this->view = Mat4f::lookAt(this->position, this->position + this->front, this->up); 
}

