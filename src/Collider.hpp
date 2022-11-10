#pragma once

#include <vector>

#include "SDL.h"
#include "Vectors.hpp"
#include "Geometry.hpp"

#include <iostream>

using namespace orgmath;

class Collider {
  protected:
    /// World position of the center-point of the collider.
    Vector2 _position{};
    Vector2 _pendingPosition{};
    float _width;
    float _height;
    double _angle = 0;

    bool _movementPending = false;
    bool _collisionDetected = false;

  public:

    /// Constructor.
    Collider();

    /// Destructor.
    ~Collider();

    /// Get the entities position as a 2d vector.
    Vector2 getPosition() const { return _position; }

    /// Get the entities width and height as a 2d vector.
    Vector2 getDimensions() const { return {_width, _height}; }

    /// Set the entities position with a 2d vector
    void setPosition(Vector2 position);

    /// Set the entities position with an x and a y coordinate.
    void setPosition(float x, float y);

    void setDimensions(Vector2 dimension);

    void setWidth(float width) { _width = width; }

    void setHeight(float height) { _height = height; }

    Rectangle<float> relativeToWorldPos(const Rectangle<float>& rect);

    void moveTo(const Vector2& desiredPosition);

    void move(const Vector2& desiredMovement);

    void rotate(const double degreesRotated);

    [[nodiscard]] virtual std::string getStatus() const {
        std::string status{""};
        status += "-- Current position: (" + std::to_string(_position.x) + ", "
                                           + std::to_string(_position.y) + ")\n";
        status += "-- Dimensions (width/height): (" + std::to_string(_width) + ", "
                                                    + std::to_string(_height) + ")\n";
        return status;
    }

    std::string type = "";
    std::string id = "";
    bool isBlocking;
};
