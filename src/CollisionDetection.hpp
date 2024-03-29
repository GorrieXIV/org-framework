#pragma once

#include <vector>

#include "Geometry.hpp"
#include "PolygonCollider.hpp"

using namespace orgmath;

namespace orgphysics {

bool collisionDetected(const Rectangle<float>& recA,
                       const Rectangle<float>& recB);

bool collisionDetectedBySAT(const PolygonCollider& colliderA,
                            const PolygonCollider& colliderB);

bool collisionDetectedBySAT(const PolygonCollider& colliderA,
                            const PolygonCollider& colliderB,
                            float& overlap);

bool separatedByAxis(const PolygonCollider& colliderA,
                     const PolygonCollider& colliderB);

bool separatedByAxis(const PolygonCollider& colliderA,
                     const PolygonCollider& colliderB,
                     float& overlap);

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
