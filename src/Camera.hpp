#pragma once

#include "SDL.h"
#include "Window.hpp"
#include "Vectors.hpp"

class Camera {
public:
    Camera(Vector2 initialPosition);
    Camera(float x, float y);
    Camera() = default;

    Vector2 position{};
};
