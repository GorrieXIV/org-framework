#pragma once

#include <vector>

#include "Geometry.hpp"
#include "PolygonCollider.hpp"

using namespace orgmath;

namespace orgphysics {

bool collisionDetected(const Rectangle<float>& recA,
                       const Rectangle<float>& recB);

bool collisionDetected(const PolygonCollider& colliderA,
                       const PolygonCollider& colliderB);

bool separatedByAxis(const PolygonCollider& colliderA,
                     const PolygonCollider& colliderB);

bool collisionDetectedFromDiagonal(const PolygonCollider& colliderA,
                                   const PolygonCollider& colliderB);

bool checkDiagonalOverlaps(const PolygonCollider& colliderA,
                           const PolygonCollider& colliderB,
                           Vector2& displacementA,
                           Vector2& displacementB);

bool diagonalFound(const PolygonCollider& colliderA,
                   const PolygonCollider& colliderB,
                   Vector2& diplacementVector);

}; // namespace orgphysics
