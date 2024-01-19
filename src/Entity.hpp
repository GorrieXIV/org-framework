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

    /// Get the constant forces acting on this entity.
    const std::vector<Vector2>& getActiveForces() const { return _activeForces; }

    /// Set the entities position with a 2d vector
    void setPosition(Vector2 position);

    /// Set the entities position with an x and a y coordinate.
    void setPosition(float x, float y);

    void setDimensions(Vector2 dimension);

    void setWidth(float width) { _width = width; }

    void setHeight(float height) { _height = height; }

    Rectangle<float> relativeToWorldPos(const Rectangle<float>& rect);

    PolygonCollider getLookAheadCollider() const {
        auto lookAheadCollider = collider;
        lookAheadCollider.moveTo(_pendingPosition + acceleration);
        lookAheadCollider.rotate(_pendingRotation);
        return lookAheadCollider;
    }

    void moveTo(const Vector2& desiredPosition);

    void move(const Vector2& desiredMovement);

    void rotate(const double degreesRotated);

    /// Used by the physics engine to finalize movements after is has determined
    /// that there is no blocking collision.
    void resolvePendingActions();

    void applyForce(const Vector2& f);

    void applyConstantForce(Vector2 force);

    /// Use this function to tell `this` that it collided with another Entity.
    virtual void triggerCollision(const Entity& collidingEntity, const float& overlap) {
        if (collidingEntity.type == "blocking") {
            _collisionDetected = true;

            // If an overlap was found, displace the entity.
            if (overlap != 0.0f) {
                auto travelVector = _pendingPosition + acceleration - _position;
                auto s = sqrtf(travelVector.x * travelVector.x +
                               travelVector.y * travelVector.y);
                
                if (s == 0.0f) {
                    return;
                }

                Vector2 displacement = {overlap * travelVector.x / s,
                                        overlap * travelVector.y / s};
                _pendingPosition -= displacement;

                if (overlap != 0.0f && displacement.y > 0 || collidingEntity.id == "ground") {
                    _groundedPending = true;
                }
            }
        }
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
    std::string id = "UNSET ENTITY ID";
    PolygonCollider collider{};
    bool frameProcessed = false;
    bool isFixed = false;
    bool grounded = false;
    Vector2 acceleration{};

  protected:
    Vector2 _position{};
    Vector2 _pendingPosition{};
    Vector2 _pendingMovement{};
    float _width;
    float _height;
    double _angle = 0;
    double _pendingRotation = 0;
    bool _collisionDetected = false;
    bool _groundedPending = false;

    std::vector<Hitbox> _hitboxes{};
    std::vector<Vector2> _activeForces{};
};
