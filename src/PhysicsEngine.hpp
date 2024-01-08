#pragma once

#include <vector>
#include <memory>

#include "Geometry.hpp"
#include "CollisionDetection.hpp"
#include "Entity.hpp"

using namespace orgmath;

namespace orgphysics {

enum CollisionAlgorithm {
    SAT,
    SAT_RESOLVED,
    DIAGONAL,
    DIAGONAL_RESOLVED
};

class PhysicsEngine {
  public:
    /// Default Constructor.
    PhysicsEngine();

    /// Destructor.
    ~PhysicsEngine();

    /// Add an entity to the once-per-frame collision check.
    void addEntity(Entity& entity);

    /// To be called every frame for most cases.
    /// Applies forces and checks for/triggers collisions.
    void update();

    void addGlobalForce(Vector2 force);

  private:
    void _applyForces();
    void _checkCollisions();

    std::vector<std::shared_ptr<Entity>> _entities;
    std::vector<Vector2> _globalForces;
    CollisionAlgorithm _collisionAlgorithm = DIAGONAL_RESOLVED;
};

}; // namespace orgphysics
