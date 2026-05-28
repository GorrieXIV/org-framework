#include "DiagonalCollisions.hpp"

namespace orgphysics {

bool collisionDetectedFromDiagonal(const PolygonCollider& colliderA,
                                   const PolygonCollider& colliderB)
{
    // Check for base cases like unintialized colliders.
    if (!colliderA.vertices.size() || !colliderB.vertices.size()) {
        return false;
    }

    // Check diagonals of A against B.
    if (diagonalOverlapFound(colliderA, colliderB)) {
        return true;
    }

    // Check diagonals of B against A.
    if (diagonalOverlapFound(colliderB, colliderA)) {
        return true;
    }

    return false;
}

void checkDiagonalOverlaps(const PolygonCollider& colliderA,
                           const PolygonCollider& colliderB,
                           Vector2& displacementA,
                           Vector2& displacementB)
{
    // Check for base cases like unintialized colliders.
    if (!colliderA.vertices.size() || !colliderB.vertices.size()) {
        return;
    }

    // Check diagonals of A against B and B against A.
    checkDiagonalOverlap(colliderA, colliderB, displacementB);
    checkDiagonalOverlap(colliderB, colliderA, displacementA);
}

bool diagonalOverlapFound(const PolygonCollider& colliderA,
                          const PolygonCollider& colliderB)
{
    auto verticesA = colliderA.vertices;
    auto verticesB = colliderB.vertices;

    for (int p = 0; p < verticesA.size(); p++) {
        auto lineAStart = colliderA.getPosition();
        auto lineAEnd   = verticesA[p];

        for (int q = 0; q < verticesB.size(); q++) {
            auto lineBStart = verticesB[q];
            auto lineBEnd = verticesB[(q + 1) % verticesB.size()];

            auto h = (lineBEnd.x - lineBStart.x) * (lineAStart.y - lineAEnd.y)
                   - (lineAStart.x - lineAEnd.x) * (lineBEnd.y - lineBStart.y);
            auto t1 = ((lineBStart.y - lineBEnd.y) * (lineAStart.x - lineBStart.x)
                    + (lineBEnd.x - lineBStart.x) * (lineAStart.y - lineBStart.y)) / h;
            auto t2 = ((lineAStart.y - lineAEnd.y) * (lineAStart.x - lineBStart.x)
                    + (lineAEnd.x - lineAStart.x) * (lineAStart.y - lineBStart.y)) / h;

            if (t1 >= 0.0f && t1 < 1.0f && t2 > 0.0f && t2 < 1.0f) {
                return true;
            }
        }
    }

    return false;
}

bool checkDiagonalOverlap(const PolygonCollider& colliderA,
                          const PolygonCollider& colliderB,
                          Vector2& displacementVector)
{
    auto verticesA = colliderA.vertices;
    auto verticesB = colliderB.vertices;

    for (int p = 0; p < verticesA.size(); p++) {
        auto lineAStart = colliderA.getPosition();
        auto lineAEnd   = verticesA[p];

        for (int q = 0; q < verticesB.size(); q++) {
            auto lineBStart = verticesB[q];
            auto lineBEnd = verticesB[(q + 1) % verticesB.size()];

            auto h = (lineBEnd.x - lineBStart.x) * (lineAStart.y - lineAEnd.y)
                   - (lineAStart.x - lineAEnd.x) * (lineBEnd.y - lineBStart.y);
            auto t1 = ((lineBStart.y - lineBEnd.y) * (lineAStart.x - lineBStart.x)
                    + (lineBEnd.x - lineBStart.x) * (lineAStart.y - lineBStart.y)) / h;
            auto t2 = ((lineAStart.y - lineAEnd.y) * (lineAStart.x - lineBStart.x)
                    + (lineAEnd.x - lineAStart.x) * (lineAStart.y - lineBStart.y)) / h;

            if (t1 >= 0.0f && t1 < 1.0f && t2 > 0.0f && t2 < 1.0f) {
                displacementVector.x += (1.0f - t1) * (lineAEnd.x - lineAStart.x);
                displacementVector.y -= (1.0f - t2) * (lineAEnd.y - lineAStart.y);
            }
        }
    }

    return false;
}

}; // namespace orgphysics
