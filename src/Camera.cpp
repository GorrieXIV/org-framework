#include "Camera.hpp"

Camera::Camera(Vector2 initialPosition) : position{initialPosition} { }

Camera::Camera(float x, float y) : position{x, y} { }

void Camera::move(float dx, float dy)
{
    std::cout << "moving camera" << std::endl;
    auto newX = position.x + dx;
    if (newX <= SCREEN_WIDTH && newX >= -1 * SCREEN_WIDTH) {
        position.x += dx;
    }

    auto newY = position.y + dy;
    if (newY <= SCREEN_HEIGHT && newY >= -1 * SCREEN_HEIGHT) {
        position.y += dy;
    }
}
