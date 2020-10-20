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
        std::cout << A->getStatus() << std::endl;
        for (const auto& B : _entities) {
            if (A->temp_getHitbox() == B->temp_getHitbox()) continue;
            if (collisionDetected(A->temp_getHitbox(), B->temp_getHitbox())) {
                A->triggerCollision();
                B->triggerCollision();
            }
        }
    }
}

void PhysicsEngine::addEntity(Entity& entity)
{
    auto entitySharedPtr = std::shared_ptr<Entity>(&entity);
    _entities.push_back(entitySharedPtr);
}

}; // namespace orgphysics
