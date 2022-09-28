#include "Entity.hpp"

Entity::Entity()
{
    _position.x = 0.0f;
    _position.y = 0.0f;
}

Rectangle<float> Entity::relativeToWorldPos(const Rectangle<float>& rect)
{
    //FIXME: Why do we cast these positions to int and then return a float rect?
    return Rectangle<float>(int(_position.x + rect.position.x - rect.width / 2),
                            int(_position.y + rect.position.y - rect.height / 2),
                            int(rect.width),
                            int(rect.height));
}

Entity::~Entity() {}

void Entity::setPosition(Vector2 position)
{
    _position.x = position.x;
    _position.y = position.y;
}

void Entity::setPosition(float x, float y)
{
    _position.x = x;
    _position.y = y;
}

void Entity::moveTo(const Vector2& desiredPosition)
{
    _pendingPosition = desiredPosition;
    _movementPending = true;
}

void Entity::move(const Vector2& desiredMovement)
{
    _pendingPosition = _position + desiredMovement;
    _movementPending = true;
}

void Entity::rotate(const double degreesRotated)
{
    _angle += degreesRotated;
}
