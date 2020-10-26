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
            if (A->temp_getHitbox() == B->temp_getHitbox()) continue;
            if (collisionDetected(A->temp_getHitbox(), B->temp_getHitbox())) {
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
