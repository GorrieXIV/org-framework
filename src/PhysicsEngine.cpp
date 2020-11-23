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
            auto hitboxA = A->temp_getHitbox();
            auto hitboxB = B->temp_getHitbox();

            // If A and B are the same entity, skip.
            if (hitboxA == hitboxB) continue;

            // If A or B have only a "null" hitbox, skip.
            if (hitboxA.isNull() || hitboxB.isNull()) continue;

            // If A and B coincide, alert both entities of the collision.
            if (collisionDetected(hitboxA, hitboxB)) {
                A->triggerCollision(*B);
                B->triggerCollision(*A);
            }
        }
        A->resolvePendingActions();
    }
}

void PhysicsEngine::addEntity(Entity& entity)
{
    auto entitySharedPtr = std::shared_ptr<Entity>(&entity);
    _entities.push_back(entitySharedPtr);
}

}; // namespace orgphysics
