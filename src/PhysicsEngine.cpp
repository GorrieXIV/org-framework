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

        netUnitForce += netGlobalForce;
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

            // If A and B coincide, alert both entities of the collision.
            if (collisionDetected(hitboxA, hitboxB)) {
                A->triggerCollision(*B);
                B->triggerCollision(*A);
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
