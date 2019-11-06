#pragma once

#include "platform.hpp"
#include "math.hpp"

class Camera {
public:
    Camera(Vector2 initialPosition);
    Camera(float x, float y);
    Camera() = default;

    Vector2 position{};
};
