#include "BasicCollisions.hpp"

namespace orgphysics {

// Basic rectangle collision detection.
bool collisionDetected(const Rectangle<float>& recA,
                       const Rectangle<float>& recB)
{
    if (recA.position.x < recB.position.x + recB.width
     && recA.position.x + recA.width > recB.position.x
     && recA.position.y < recB.position.y + recB.height
     && recA.position.y + recA.height > recB.position.y) {
        return true;
    }

    return false;
}

}; // namespace orgphysics
