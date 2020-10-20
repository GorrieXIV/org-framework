#pragma once

#include <vector>
#include <memory>

#include "Geometry.hpp"
#include "CollisionDetection.hpp"
#include "Entity.hpp"

using namespace orgmath;

namespace orgphysics {

class PhysicsEngine {
  public:
    /// Default Constructor.
    PhysicsEngine();

    /// Destructor.
    ~PhysicsEngine();

    /// Check for collisions on the current frame.
    void checkCollisions();

    /// Add an entity to the once-per-frame collision check.
    void addEntity(Entity& entity);

  private:
    std::vector<std::shared_ptr<Entity>> _entities;
};

}; // namespace orgphysics
