#ifndef INC_SETTINGS_H_
#define INC_SETTINGS_H_

#include <vector>
#include "Vec3f.h"

#define ANSI_RESET "\033[0m"
#define ANSI_COLOR_YELLOW "\033[33m"
#define ANSI_COLOR_CYAN "\033[36m"

constexpr unsigned int WIN_WIDTH = 1200;
constexpr unsigned int WIN_HEIGHT = 900;
constexpr float ASPECT_RATIO = static_cast<float>(WIN_WIDTH) / static_cast<float>(WIN_HEIGHT);

// Colors
const Vec3f clearColor = {0.094f, 0.094f, 0.145f};
// Catppuccin mocha
const std::vector<Vec3f> palette = {
    {0.961f, 0.878f, 0.863f}, // Rosewater
    {0.949f, 0.804f, 0.804f}, // Flamingo
    {0.961f, 0.761f, 0.906f}, // Pink
    {0.796f, 0.651f, 0.969f}, // Mauve
    {0.953f, 0.545f, 0.659f}, // Red
    {0.922f, 0.627f, 0.675f}, // Maroon
    {0.980f, 0.702f, 0.529f}, // Peach
    {0.976f, 0.886f, 0.686f}, // Yellow
    {0.651f, 0.890f, 0.631f}, // Green
    {0.580f, 0.886f, 0.835f}, // Teal
    {0.537f, 0.863f, 0.922f}, // Sky
    {0.455f, 0.780f, 0.925f}, // Sapphire
    {0.537f, 0.706f, 0.980f}, // Blue
    {0.706f, 0.745f, 0.996f}, // Lavender
    // {0.804f, 0.839f, 0.957f}  // Text
};

// Model settings
const float MOVEMENT_SPEED = 1.5f;

// Camera settings
const Vec3f CAM_START_POSITION = Vec3f(0.0f, 0.0f, 10.0f);
const Vec3f UP_DIR = Vec3f(0.0f, 1.0f, 0.0f);

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float ZOOM = 45.0f;

const float NEAR_CLIP = 0.1f;
const float FAR_CLIP = 500.0f;

const float ZOOM_SPEED = 10.0f;

#endif  //INC_SETTINGS_H_
