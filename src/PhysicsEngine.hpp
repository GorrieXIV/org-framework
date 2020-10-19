#pragma once

#include <vector>

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

  private:
    std::vector<Entity> _entities;
};

}; // namespace orgphysics
