#pragma once

#include <vector>

#include "Geometry.hpp"
#include "PolygonCollider.hpp"

using namespace orgmath;

namespace orgphysics {

bool collisionDetectedFromDiagonal(const PolygonCollider& colliderA,
                                   const PolygonCollider& colliderB);

void checkDiagonalOverlaps(const PolygonCollider& colliderA,
                           const PolygonCollider& colliderB,
                           Vector2& displacementA,
                           Vector2& displacementB);

bool checkDiagonalOverlap(const PolygonCollider& colliderA,
                          const PolygonCollider& colliderB,
                          Vector2& diplacementVector);

bool diagonalOverlapFound(const PolygonCollider& colliderA,
                          const PolygonCollider& colliderB);

}; // namespace orgphysics
