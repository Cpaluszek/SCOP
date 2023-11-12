#include "../inc/Camera.h"

Camera::Camera(Vec3f position, Vec3f up, float yaw, float pitch)
    : front(Vec3f(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), zoom(ZOOM) {
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

Mat4f Camera::getViewMatrix() const {
    return Mat4f::lookAt(this->position, this->position + this->front, this->up);
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

void Camera::processKeyboardInput(Camera_Movement direction, float deltaTime) {
   float velocity = this->movementSpeed * deltaTime;

   // Todo: manage multiple keys at the same time
   if (direction == FORWARD) {
       this->position += this->front * velocity;
   } else if (direction == BACKWARD) {
       this->position -= this->front * velocity;
   } else if (direction == RIGHT) {
       this->position += this->right* velocity;
   } else if (direction == LEFT) {
       this->position -= this->right * velocity;
   }

   // Todo: rotate
}
