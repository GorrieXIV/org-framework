#include "PolygonCollider.hpp"

#include <cmath>

#define sind(x) (sin(fmod((x),360) * M_PI / 180))
#define cosd(x) (cos(fmod((x),360) * M_PI / 180))

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
    auto differenceVector = desiredPosition - _position;
    _position = desiredPosition;
    for (auto& vertex : vertices) {
        vertex.x += differenceVector.x;
        vertex.y += differenceVector.y;
    }
}

void PolygonCollider::move(const Vector2& desiredMovement)
{
    _position = _position + desiredMovement;
}

void PolygonCollider::addVertex(const Vector2& vertex)
{
    _baseVertices.emplace_back(vertex);

    // TODO: add game-space vertex based on angle of collider, so that in the future
    // we can add vertices at any point.
    vertices.emplace_back(vertex + _position);
}

void PolygonCollider::rotate(const double degreesRotated)
{
    _angle += degreesRotated;

    // Update all the world-position vertices based on new rotation.
    auto sinR = sind(_angle);
    auto cosR = cosd(_angle);
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i] = {(_baseVertices[i].x * cosR) - (_baseVertices[i].y * sinR) + _position.x,
                       (_baseVertices[i].x * sinR) + (_baseVertices[i].y * cosR) + _position.y};
    }
}
