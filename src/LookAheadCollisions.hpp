#pragma once

#include "Geometry.hpp"
#include "Entity.hpp"
#include "Lines.hpp"
#include "PolygonCollider.hpp"

using namespace orgmath;

namespace orgphysics {

/// Look-Ahead collision detection is intended to be used only when comparing a rigid or free
/// collider with a fixed collider. Because one collider is fixed, we know it will not be moving
/// and can make assumptions about it that save on computation. If the algorithm were generalized,
/// it would likely be less performant than SAT or Diagonals - but with this optimization we get
/// the improved displacement/correction accuracy of Look-Ahead without suffering performance
/// losses.
bool collisionDetectedByLookAhead(const Entity& movingEntity,
                                  const PolygonCollider& fixedCollider,
                                  const Vector2& overlap);

}; // namespace orgphysics
