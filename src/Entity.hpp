#pragma once

#include <vector>

#include "SDL.h"
#include "Vectors.hpp"
#include "Geometry.hpp"

#include <iostream>

using namespace orgmath;

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

    Rectangle<float> temp_getHitbox() const {
        auto hb = _hitboxes.front();
        auto position = _movementPending ? _pendingPosition : _position;
        return Rectangle<float>(hb.position.x + position.x - hb.width / 2,
                                hb.position.y + position.y - hb.height / 2,
                                hb.width,
                                hb.height);
    }

    void moveTo(const Vector2& desiredPosition);

    /// Used by the physics engine to finalize movements after is has determined
    /// that there is no blocking collision.
    void resolvePendingActions() {
        if (_movementPending && !_collisionDetected) {
            _position = _pendingPosition;
        }

        _movementPending = false;
        _collisionDetected = false;
    }

    /// Use this function to tell `this` that it collided with another Entity.
    virtual void triggerCollision(const Entity& collidingEntity) {
        _collisionDetected = true;
    }

    virtual std::string getStatus() const = 0;

  protected:
    Vector2 _position{};
    Vector2 _pendingPosition{};
    float _width;
    float _height;
  
    bool _movementPending = false;
    bool _collisionDetected = false;

    std::vector<Rectangle<float>> _hitboxes{};
};
