#include <vector>
#include <tuple>

#include "LookAheadCollisions.hpp"

namespace orgphysics {

// (Fixed edge, Translation vector, distance to intersection)
using IntersectionTuple = std::tuple<Vector2, Vector2, float>;

bool collisionDetectedByLookAhead(const Entity& movingEntity,
                                  const PolygonCollider& fixedCollider,
                                  const Vector2& displacement)
{
    std::vector<IntersectionTuple> intersections{};
    std::vector<LineSegment> colliderEdges{};

    auto startCollider = movingEntity.collider;
    auto endCollider   = movingEntity.getLookAheadCollider();

    // Construct list of the fixed collider's edges.
    auto fixedVertices = fixedCollider.vertices;
    for (int a = 0; a < fixedVertices.size(); a++) {
        // Get adjacent point.
        int b = (a + 1) % fixedVertices.size();
        colliderEdges.push_back({fixedVertices[a], fixedVertices[b]});
    }

    // Check the translation vectors of all the vertices of the moving entity, from its current
    // position to it's next. Keep track of any that intersect with an edge on the fixed collider.
    // WARNING: Assumes number of vertices in the entities collider hasn't changed on this frame.
    for (int i = 0; i < startCollider.vertices.size(); i++) {
        // if intersection detected between an edge and latest translation vector,
        // add it to the list of intersections.
        //
        // To find intersections: we can rewrite (P, R) as (P, P+a) and (Q, S) as (Q, Q+b).
        // Under this framing we know there is a values t and v whereupon these line segments
        // intersect at P+ta or Q+vb (the same point in space).
        // Thus we can find one (let's go with t) by evaluating t = ((Q - P) * b) / (a * b)
        //
        // Here, (P, R) will be the current translation vector, and (Q, S) is the current
        // fixed collider edge.
        LineSegment PR(startCollider.vertices[i], endCollider.vertices[i]);

        for (const auto& QS : colliderEdges) {
            // We can then evaluate a and b by subtracting P from R and Q from S, respectively.
            auto a = PR.end - PR.start;
            auto b = QS.end - QS.start;

            // Now solve for t.
            auto t = ((QS.start - PR.start) * b) / (a * b);
        }
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

bool segmentsIntersect()
{
    // return counterClockwiseTriplet()
    return true;
}

// This function determines if a triplet of points is given in counter-clockwise order.
// The triplet (A, B, C) is counter-clockwise if the line AB has a smaller slope than the line AC.
bool counterClockwiseTriplet(Vector2& A, Vector2& B, Vector2& C)
{
    return (C.y - A.y) * (B.x - A.x) > (B.y - A.y) * (C.x - A.x);
}

}; // namespace orgphysics
