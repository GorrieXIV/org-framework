#pragma once

#include <vector>
#include <iostream>

#include "SDL.h"
#include "Vectors.hpp"
#include "Geometry.hpp"
#include "Collider.hpp"

using namespace orgmath;

class PolygonCollider : Collider {
  protected:
    /// Vector of vertices for the polygon.
    /// TODO: Switch to WorldPos type eventually.
    std::vector<Vector2>  _vertices{};

  public:
    /// Constructor.
    PolygonCollider();

    /// Destructor.
    ~PolygonCollider();

    /// Get the entities position as a 2d vector.
    Vector2 getPosition() const { return _position; }

    /// Get the entities width and height as a 2d vector.
    Vector2 getDimensions() const { return {_width, _height}; }

    /// Set the entities position with a 2d vector
    void setPosition(Vector2 position);

    /// Set the entities position with an x and a y coordinate.
    void setPosition(float x, float y);

    void moveTo(const Vector2& desiredPosition);

    void move(const Vector2& desiredMovement);

    void rotate(const double degreesRotated);

    std::string type = "";
    std::string id = "";
    bool isBlocking;
};
