#include "PolygonCollider.hpp"

PolygonCollider::PolygonCollider()
{
    _position.x = 0.0f;
    _position.y = 0.0f;
}

PolygonCollider::~PolygonCollider() {}

void PolygonCollider::setPosition(Vector2 position)
{
    _position.x = position.x;
    _position.y = position.y;
}

void PolygonCollider::setPosition(float x, float y)
{
    _position.x = x;
    _position.y = y;
}

void PolygonCollider::moveTo(const Vector2& desiredPosition)
{
    // OLD moveTo code:
    // _pendingPosition = desiredPosition;
    // _movementPending = true;
    
    // Temporary moveTo:
    _position = desiredPosition;
}

void PolygonCollider::move(const Vector2& desiredMovement)
{
    // OLD move code:
    // _pendingPosition = _position + desiredMovement;
    // _movementPending = true;

    // Temporary move:
    _position = _position + desiredMovement;
}

void PolygonCollider::rotate(const double degreesRotated)
{
    // OLD rotate code:
    // _angle += degreesRotated;
}
