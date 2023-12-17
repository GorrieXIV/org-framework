#include "PhysicsEngine.hpp"

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


            Vector2 displacementA = {0, 0};
            Vector2 displacementB = {0, 0};

            // If A and B coincide, alert both entities of the collision.
            checkDiagonalOverlaps(hitboxA, hitboxB, displacementA, displacementB);
            if (!displacementA.isNull() || !displacementB.isNull()) {
                if (A->isFixed && B->isFixed) {
                    displacementA = {0, 0};
                    displacementB = {0, 0};
                } else if (A->isFixed && !B->isFixed) {
                    displacementB -= displacementA;
                    displacementA = {0, 0};
                } else if (B->isFixed && !A->isFixed) {
                    displacementA -= displacementB;
                    displacementB = {0, 0};
                }

                A->triggerCollision(*B, displacementA);
                B->triggerCollision(*A, displacementB);
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
