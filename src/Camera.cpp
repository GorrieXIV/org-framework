#include "Camera.hpp"

Camera::Camera(Vector2 initialPosition)
: position{initialPosition}
{
   std::cout << "Initializing camera..." << std::endl;
}

Camera::Camera(float x, float y)
: position{x, y}
{
   std::cout << "Initializing camera..." << std::endl;
}
