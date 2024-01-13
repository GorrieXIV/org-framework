#include "PhysicsEngine.hpp"

#include <exception>

namespace orgphysics {

PhysicsEngine:: PhysicsEngine()
{

}

PhysicsEngine:: ~PhysicsEngine()
{

}

void PhysicsEngine:: addEntity(Entity& entity)
{
    auto entitySharedPtr = std::shared_ptr<Entity>(&entity);
    _entities.push_back(entitySharedPtr);
}

void PhysicsEngine:: update()
{
    _applyForces();
    _checkCollisions();
}

void PhysicsEngine:: addGlobalForce(Vector2 force)
{
    _globalForces.push_back(force);
}

void PhysicsEngine:: _applyForces()
{
    // Summize global forces.
    Vector2 netGlobalForce{};
    for (const auto& F : _globalForces) {
        netGlobalForce += F;
    }

    Vector2 netUnitForce{};
    for (const auto& A : _entities) {
        if (A->isFixed) {
            continue;
        }

        for (const auto& F : A->getActiveForces()) {
            netUnitForce += F;
        }

        if (!A->grounded) {
            netUnitForce += netGlobalForce;
        }

        A->acceleration += netUnitForce;
    }
}

void PhysicsEngine:: _checkCollisions()
{
    for (const auto& A : _entities) {
        for (const auto& B : _entities) {
            // Skip this entity if it has already been fully processed.
            if (B->frameProcessed) {
                continue;
            }

            // Don't check entities against themselves.
            if (A == B) {
                continue;
            }

            auto hitboxA = A->getLookAheadCollider();
            auto hitboxB = B->getLookAheadCollider();
            float overlapA = 0.0f;
            float overlapB = 0.0f;
            bool collisionDetected = false;

            switch (_collisionAlgorithm) {
                case SAT: {
                    collisionDetected = collisionDetectedBySAT(hitboxA, hitboxB);
                    break;
                }
                case SAT_RESOLVED: {
                    float overlap = 0.0f;
                    collisionDetected = collisionDetectedBySAT(hitboxA, hitboxB, overlap);

                    if (A->isFixed && !B->isFixed) {
                        overlapB = overlap;
                    } else if (B->isFixed && !A->isFixed) {
                        overlapA = overlap;
                    }

                    break;
                }
                case DIAGONAL: {
                    collisionDetected = collisionDetectedFromDiagonal(hitboxA, hitboxB);
                    break;
                }
                case DIAGONAL_RESOLVED: {
                    std::throw_with_nested("Resolved diagonals not currently supported");

                    //TODO: Update diagonals so it returns an overlap value instead of a displacement vector.

                    //checkDiagonalOverlaps(hitboxA, hitboxB, displacementA, displacementB);
                    //collisionDetected = !displacementA.isNull() || !displacementB.isNull();

                    //if (A->isFixed && !B->isFixed) {
                    //    displacementB += displacementA;
                    //    displacementB = displacementB * -1;
                    //    displacementA = {0, 0};
                    //} else if (B->isFixed && !A->isFixed) {
                    //    displacementA += displacementB;
                    //    displacementA = displacementA * -1;
                    //    displacementB = {0, 0};
                    //}

                    break;
                }
            }

            // If A and B coincide, alert both entities of the collision.
            if (collisionDetected) {
                A->triggerCollision(*B, overlapA);
                B->triggerCollision(*A, overlapB);
            }
        }

        A->frameProcessed = true;
        A->resolvePendingActions();
    }

    for (const auto& A : _entities) {
        A->frameProcessed = false;
    }
}

}; // namespace orgphysics
