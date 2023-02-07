#pragma once

#include <vector>

#include "SDL.h"
#include "Vectors.hpp"
#include "Geometry.hpp"
#include "PolygonCollider.hpp"

#include <iostream>

using namespace orgmath;

// Hitboxes stored as <Rect, isBlocking>
using Hitbox = std::pair<Rectangle<float>, bool>;

/* ENTITY CLASS ------------------------------------------- */
class Entity {
  public:

    /// Constructor.
    Entity();

    /// Destructor.
    ~Entity();

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

    PolygonCollider getCollider() const {
        auto lookAheadCollider = _tempCollider;
        lookAheadCollider.moveTo(_pendingPosition);
        lookAheadCollider.rotate(_pendingRotation);
        return lookAheadCollider;
    }

    void moveTo(const Vector2& desiredPosition);

    void move(const Vector2& desiredMovement);

    void rotate(const double degreesRotated);

    /// Used by the physics engine to finalize movements after is has determined
    /// that there is no blocking collision.
    void resolvePendingActions() {
        if (!_collisionDetected) {
            if (_movementPending) {
                _position = _pendingPosition;
                _tempCollider.moveTo(_pendingPosition);
            }

            if (_rotationPending) {
                _angle += _pendingRotation;
                _tempCollider.rotate(_pendingRotation);
            }
        }

        _pendingPosition = _position;
        _pendingRotation = 0;
        _movementPending = false;
        _rotationPending = false;
        _collisionDetected = false;
    }

    /// Use this function to tell `this` that it collided with another Entity.
    virtual void triggerCollision(const Entity& collidingEntity) {
        _collisionDetected = true;
    }

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
    bool frameProcessed = false;

  protected:
    Vector2 _position{};
    Vector2 _pendingPosition{};
    float _width;
    float _height;
    double _angle = 0;
    double _pendingRotation = 0;

    bool _movementPending = false;
    bool _rotationPending = false;
    bool _collisionDetected = false;

    std::vector<Hitbox> _hitboxes{};
    PolygonCollider _tempCollider{};
};
