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

bool dividedByADiagonal(const PolygonCollider& colliderA,
                        const PolygonCollider& colliderB);

bool diagonalFound(const PolygonCollider& colliderA,
                   const PolygonCollider& colliderB);

}; // namespace orgphysics
