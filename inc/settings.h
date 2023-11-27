#ifndef INC_SETTINGS_H_
#define INC_SETTINGS_H_

#include "Vec3f.h"

#define ANSI_RESET "\033[0m"
#define ANSI_COLOR_YELLOW "\033[33m"
#define ANSI_COLOR_CYAN "\033[36m"

constexpr unsigned int WIN_WIDTH = 1200;
constexpr unsigned int WIN_HEIGHT = 900;
constexpr float ASPECT_RATIO = static_cast<float>(WIN_WIDTH) / static_cast<float>(WIN_HEIGHT);

// Model settings
const float MOVEMENT_SPEED = 1.5f;

// Camera settings
const Vec3f START_POSITION = Vec3f(0.0f, 0.0f, 10.0f);
const Vec3f UP_DIR = Vec3f(0.0f, 1.0f, 0.0f);

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float ZOOM = 45.0f;

const float NEAR_CLIP = 0.1f;
const float FAR_CLIP = 500.0f;

const float ZOOM_SPEED = 10.0f;

#endif  //INC_SETTINGS_H_
