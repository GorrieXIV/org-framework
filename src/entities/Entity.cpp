#include "Entity.hpp"

Entity::Entity()
{
    _position.x = 0.0f;
    _position.y = 0.0f;
}

std::string Entity::getStatus() const
{
    std::string status{""};
    status += "-- Current position: (" + std::to_string(_position.x) + ", " + std::to_string(_position.y) + ")\n";
    status += "-- Dimensions (width/height): (" + std::to_string(_width) + ", " + std::to_string(_height) + ")\n";

    return status;
}

Rectangle Entity::relativeToWorldPos(const Rectangle& rect)
{
    return Rectangle(int(_position.x + rect.position.x - rect.width / 2),
                     int(_position.y + rect.position.y - rect.height / 2),
                     int(rect.width),
                     int(rect.height));
}

Entity::~Entity() {}

Vector2 Entity::getPosition() const
{
    return _position;
}

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
