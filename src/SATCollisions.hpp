#pragma once

#include <vector>

#include "Geometry.hpp"
#include "PolygonCollider.hpp"

using namespace orgmath;

namespace orgphysics {

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
}; // namespace orgphysics
