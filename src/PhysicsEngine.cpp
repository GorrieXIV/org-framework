#include "PhysicsEngine.hpp"

namespace orgphysics {

PhysicsEngine::PhysicsEngine()
{

}

PhysicsEngine::~PhysicsEngine()
{

}

void PhysicsEngine::checkCollisions()
{
    for (const auto& A : _entities) {
        for (const auto& B : _entities) {
            // Skip this entity if it has already been fully processed.
            if (B->frameProcessed) {
                continue;
            }
            auto hitboxA = A->temp_getHitbox();
            auto hitboxB = B->temp_getHitbox();

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

void PhysicsEngine::addEntity(Entity& entity)
{
    auto entitySharedPtr = std::shared_ptr<Entity>(&entity);
    _entities.push_back(entitySharedPtr);
}

}; // namespace orgphysics
