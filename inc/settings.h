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
// const std::vector<Vec3f> palette = {
//     {0.961f, 0.878f, 0.863f}, {0.949f, 0.804f, 0.804f}, {0.961f, 0.761f, 0.906f},
//     {0.796f, 0.651f, 0.969f}, {0.953f, 0.545f, 0.659f}, {0.922f, 0.627f, 0.675f},
//     {0.980f, 0.702f, 0.529f}, {0.976f, 0.886f, 0.686f}, {0.651f, 0.890f, 0.631f},
//     {0.580f, 0.886f, 0.835f}, {0.537f, 0.863f, 0.922f}, {0.455f, 0.780f, 0.925f},
//     {0.537f, 0.706f, 0.980f}, {0.706f, 0.745f, 0.996f}
// };

// APOLLO
// const std::vector<Vec3f> palette = {
//     {0.090f, 0.125f, 0.220f}, {0.145f, 0.227f, 0.369f}, {0.235f, 0.369f, 0.545f},
//     {0.310f, 0.561f, 0.729f}, {0.451f, 0.745f, 0.827f}, {0.643f, 0.867f, 0.859f},
//     {0.098f, 0.200f, 0.176f}, {0.145f, 0.337f, 0.180f}, {0.275f, 0.510f, 0.196f},
//     {0.459f, 0.655f, 0.263f}, {0.659f, 0.792f, 0.345f}, {0.816f, 0.855f, 0.569f},
//     {0.302f, 0.169f, 0.196f}, {0.478f, 0.282f, 0.255f}, {0.678f, 0.467f, 0.341f},
//     {0.753f, 0.580f, 0.451f}, {0.843f, 0.710f, 0.580f}, {0.906f, 0.835f, 0.702f},
//     {0.204f, 0.110f, 0.153f}, {0.376f, 0.173f, 0.173f}, {0.533f, 0.294f, 0.169f},
//     {0.745f, 0.467f, 0.169f}, {0.871f, 0.620f, 0.255f}, {0.910f, 0.757f, 0.439f},
//     {0.141f, 0.082f, 0.153f}, {0.255f, 0.114f, 0.192f}, {0.459f, 0.141f, 0.220f},
//     {0.647f, 0.188f, 0.188f}, {0.812f, 0.341f, 0.235f}, {0.855f, 0.525f, 0.243f},
//     {0.118f, 0.114f, 0.224f}, {0.251f, 0.153f, 0.318f}, {0.478f, 0.212f, 0.482f}
// };

// MULFOLK 32
const std::vector<Vec3f> palette = {
    {0.357f, 0.651f, 0.459f}, {0.420f, 0.784f, 0.424f}, {0.670f, 0.867f, 0.392f},
    {0.988f, 0.937f, 0.553f}, {1.000f, 0.722f, 0.474f}, {0.918f, 0.384f, 0.384f},
    {0.800f, 0.259f, 0.369f}, {0.635f, 0.157f, 0.345f}, {0.459f, 0.086f, 0.337f},
    {0.224f, 0.035f, 0.278f}, {0.380f, 0.094f, 0.318f}, {0.529f, 0.208f, 0.333f},
    {0.651f, 0.333f, 0.373f}, {0.784f, 0.451f, 0.451f}, {0.949f, 0.682f, 0.600f},
    {1.000f, 0.764f, 0.949f}, {0.933f, 0.561f, 0.796f}, {0.831f, 0.431f, 0.702f},
    {0.525f, 0.243f, 0.518f}, {0.124f, 0.063f, 0.165f}, {0.290f, 0.188f, 0.322f},
    {0.482f, 0.329f, 0.502f}, {0.651f, 0.522f, 0.623f}, {0.851f, 0.741f, 0.784f},
    {1.000f, 1.000f, 1.000f}, {0.682f, 0.886f, 1.000f}, {0.553f, 0.718f, 1.000f},
    {0.427f, 0.502f, 0.980f}, {0.518f, 0.396f, 0.925f}, {0.514f, 0.302f, 0.769f},
    {0.490f, 0.176f, 0.627f}
};

// Model settings
const float MOVEMENT_SPEED = 1.5f;
const float ROTATION_SPEED = 1.0f;

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
