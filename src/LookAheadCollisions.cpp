#include "LookAheadCollisions.hpp"

namespace orgphysics {

bool collisionDetectedByLookAhead(const Entity& movingEntity,
                                  const PolygonCollider& fixedCollider,
                                  const Vector2& displacement)
{
    std::vector<Vector2> translationVectors{};
    auto startCollider = movingEntity.collider;
    auto endCollider   = movingEntity.getLookAheadCollider();
    
    // Check the translation vectors of all the vertices of the moving entity, from its current
    // position to it's next. Keep track of any that intersect with an edge on the fixed collider.
    // WARNING: Assumes number of vertices in the entities collider hasn't changed on this frame.
    for (int i = 0; i < startCollider.vertices.size(); i++) {
        translationVectors.push_back(endCollider.vertices[i] - startCollider.vertices[i]);
    }

    // If there are no intersections, there is no collision.
    return false;

    // Keep only the edge of the collider that is closest to the entity's starting position.
    // This is the "first intersecting edge" (FIE), and the one where the collision occured.

    // Using the translation vectors to determine distances, find the vertex that is closest to
    // the FIE. 

    // The distance with which this point passes over the FIE is the magnitude of the displacement,
    // applied along the normal of the FIE.

}

}; // namespace orgphysics
