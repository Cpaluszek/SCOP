#include "../inc/Camera.h"

// Todo: remove parameters
Camera::Camera(const Vec3f position, const Vec3f up, const float yaw, const float pitch)
    : front(Vec3f(0.0f, 0.0f, -1.0f)), movementSpeed(MOVEMENT_SPEED), zoom(ZOOM) {
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    this->rotationSpeed = ROTATION_SPEED;
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

void Camera::processKeyboardInput(const Camera_Movement direction, const float deltaTime) {
    const float velocity = this->movementSpeed * deltaTime;

   if (direction == FORWARD) {
       this->position += this->front * velocity;
   } else if (direction == BACKWARD) {
       this->position -= this->front * velocity;
   } else if (direction == RIGHT) {
       this->position += this->right* velocity;
   } else if (direction == LEFT) {
       this->position -= this->right * velocity;
   } else if (direction == UP) {
       this->position += this->up * velocity;
   } else if (direction == DOWN) {
       this->position -= this->up * velocity;
   }

   // Todo: create function for rotation
   if (direction == ROTATE_RIGHT) {
        this->yaw += this->rotationSpeed * deltaTime;
        this->updateCameraVectors();
   } else if (direction == ROTATE_LEFT) {
        this->yaw -= this->rotationSpeed * deltaTime;
        this->updateCameraVectors();
   } else if (direction == ROTATE_UP) {
        this->pitch += this->rotationSpeed * deltaTime;
        this->updateCameraVectors();
   } else if (direction == ROTATE_DOWN) {
        this->pitch -= this->rotationSpeed * deltaTime;
        this->updateCameraVectors();
   }
}

void Camera::reset() {
    this->position = START_POSITION;
    this->up = UP_DIR;
    this->yaw = YAW;
    this->pitch = PITCH;
    updateCameraVectors();
}

