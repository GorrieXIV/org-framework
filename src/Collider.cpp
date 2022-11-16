#include "Collider.hpp"

Collider::Collider()
{
    _position.x = 0.0f;
    _position.y = 0.0f;
}

Collider::~Collider() {}

void Collider::setPosition(Vector2 position)
{
    _position.x = position.x;
    _position.y = position.y;
}

void Collider::setPosition(float x, float y)
{
    _position.x = x;
    _position.y = y;
}

void Collider::moveTo(const Vector2& desiredPosition)
{
    _pendingPosition = desiredPosition;
    _movementPending = true;
}

void Collider::move(const Vector2& desiredMovement)
{
    _pendingPosition = _position + desiredMovement;
    _movementPending = true;
}
