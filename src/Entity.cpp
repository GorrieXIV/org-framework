#include "Entity.hpp"

Entity:: Entity()
{
    _position.x = 0.0f;
    _position.y = 0.0f;
}

Rectangle<float> Entity:: relativeToWorldPos(const Rectangle<float>& rect)
{
    //FIXME: Why do we cast these positions to int and then return a float rect?
    return Rectangle<float>(int(_position.x + rect.position.x - rect.width / 2),
                            int(_position.y + rect.position.y - rect.height / 2),
                            int(rect.width),
                            int(rect.height));
}

Entity:: ~Entity() {}

void Entity:: setPosition(Vector2 position)
{
    _pendingPosition = _position = position;
}

void Entity:: setPosition(float x, float y)
{
    _position.x = x;
    _position.y = y;
    _pendingPosition = _position;
}

void Entity:: moveTo(const Vector2& desiredPosition)
{
    _pendingPosition = desiredPosition;
}

void Entity:: move(const Vector2& desiredMovement)
{
    _pendingPosition += desiredMovement;
}

void Entity:: rotate(const double degreesRotated)
{
    _pendingRotation = degreesRotated;
}

void Entity:: applyForce(const Vector2& f)
{
    acceleration += f;
}

void Entity:: applyConstantForce(Vector2 f)
{
    _activeForces.push_back(f);
}

void Entity:: resolvePendingActions() {
    if (!_collisionDetected) {
        _position = _pendingPosition + acceleration;
        collider.moveTo(_pendingPosition);

        if (_pendingRotation) {
            _angle += _pendingRotation;
            collider.rotate(_pendingRotation);
        }
    }

    _pendingPosition = _position;
    _pendingRotation = 0;
    _collisionDetected = false;
}
