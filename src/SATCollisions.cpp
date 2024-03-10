#include "SATCollisions.hpp"

#include <limits>

namespace orgphysics {

// Generic polygon-based collision detection.
// This function employs the Separating Axis Theorem
bool collisionDetectedBySAT(const PolygonCollider& colliderA,
                            const PolygonCollider& colliderB)
{
    // Check for base cases like unintialized colliders.
    if (!colliderA.vertices.size() || !colliderB.vertices.size()) {
        return false;
    }

    // Check if any axis on A separates the polygons.
    if (separatedByAxis(colliderA, colliderB)) {
        return false;
    }

    // Check if any axis on B separates the polygons.
    if (separatedByAxis(colliderB, colliderA)) {
        return false;
    }

    // No separators were found, therefore a collision has occurred.
    return true;
}

// Generic polygon-based collision detection.
// This function employs the Separating Axis Theorem
// Amount of overlap is returned as a `float`.
bool collisionDetectedBySAT(const PolygonCollider& colliderA,
                            const PolygonCollider& colliderB,
                            float& overlap)
{
    overlap = std::numeric_limits<float>::max();

    // Check for base cases like unintialized colliders.
    if (!colliderA.vertices.size() || !colliderB.vertices.size()) {
        return false;
    }

    // Check if any axis on A separates the polygons.
    if (separatedByAxis(colliderA, colliderB, overlap)) {
        return false;
    }

    // Check if any axis on B separates the polygons.
    if (separatedByAxis(colliderB, colliderA, overlap)) {
        return false;
    }

    // No separators were found, therefore a collision has occurred.
    return true;
}

// Performs separating axis theorem (SAT). Returns true if the
// polygons are separated by any axis on colliderA, and false otherwise.
bool separatedByAxis(const PolygonCollider& colliderA,
                     const PolygonCollider& colliderB)
{
    auto verticesA = colliderA.vertices;
    auto verticesB = colliderB.vertices;
    for (int a = 0; a < verticesA.size(); a++) {
        // Get the adjacent point (modulo to wrap around in case we're at the end of the vector.)
        int b = (a + 1) % verticesA.size();

        // Calculate normal to the a->b edge for projection.
        Vector2 projectionAxis = {-1 * (verticesA[b].y - verticesA[a].y),
                                  verticesA[b].x - verticesA[a].x};

        // Initialize max/min values.
        float minA = std::numeric_limits<float>::infinity();
        float maxA = -1 * std::numeric_limits<float>::infinity();

        // Project all points onto the axis using dot product.
        for (const auto& v : verticesA) {
            float projectedV = (v.x * projectionAxis.x) + (v.y * projectionAxis.y);
            minA = std::min(minA, projectedV);
            maxA = std::max(maxA, projectedV);
        }

        // Now do the same projection of points for colliderB.
        float minB = std::numeric_limits<float>::infinity();
        float maxB = -1 * std::numeric_limits<float>::infinity();
        for (const auto& v : verticesB) {
            float projectedV = (v.x * projectionAxis.x) + (v.y * projectionAxis.y);
            minB = std::min(minB, projectedV);
            maxB = std::max(maxB, projectedV);
        }

        // Check if projections of the two polygons overlap.
        // If they don't overlap, return true as we've found a separator.
        if (!(maxB >= minA && maxA >= minB)) return true;
    }

    return false;
}

// Performs separating axis theorem (SAT) while calculating the overlap if one is found.
bool separatedByAxis(const PolygonCollider& colliderA,
                     const PolygonCollider& colliderB,
                     float& overlap)
{
    auto verticesA = colliderA.vertices;
    auto verticesB = colliderB.vertices;
    for (int a = 0; a < verticesA.size(); a++) {
        // Get the adjacent point (modulo to wrap around in case we're at the end of the vector.)
        int b = (a + 1) % verticesA.size();

        // Calculate normal to the a->b edge for projection.
        Vector2 projectionAxis = {-1 * (verticesA[b].y - verticesA[a].y),
                                  verticesA[b].x - verticesA[a].x};

        // Normalize projection axis.
        float d = sqrtf(projectionAxis.x * projectionAxis.x + projectionAxis.y * projectionAxis.y);
        projectionAxis = { projectionAxis.x / d, projectionAxis.y / d };

        // Initialize max/min values.
        float minA = std::numeric_limits<float>::infinity();
        float maxA = -1 * std::numeric_limits<float>::infinity();

        // Project all points onto the axis using dot product.
        for (const auto& v : verticesA) {
            float projectedV = (v.x * projectionAxis.x) + (v.y * projectionAxis.y);
            minA = std::min(minA, projectedV);
            maxA = std::max(maxA, projectedV);
        }

        // Now do the same projection of points for colliderB.
        float minB = std::numeric_limits<float>::infinity();
        float maxB = -1 * std::numeric_limits<float>::infinity();
        for (const auto& v : verticesB) {
            float projectedV = (v.x * projectionAxis.x) + (v.y * projectionAxis.y);
            minB = std::min(minB, projectedV);
            maxB = std::max(maxB, projectedV);
        }

        // Check if projections of the two polygons overlap.
        // If they don't overlap, return true as we've found a separator.
        if (!(maxB >= minA && maxA >= minB)) return true;

        auto currentOverlap = std::min(maxA, maxB) - std::max(minA, minB);
        overlap = std::min(currentOverlap, overlap);
    }

    return false;
}

}; // namespace orgphysics