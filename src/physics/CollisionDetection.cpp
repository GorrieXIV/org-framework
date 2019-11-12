#include "CollisionDetection.hpp"

namespace orgphysics {

bool collisionDetected(const Rectangle<float>& recA, const Rectangle<float>& recB)
{
    if (recA.position.x < recB.position.x + recB.width
     && recA.position.x + recA.width > recB.position.x
     && recA.position.y < recB.position.y + recB.height
     && recA.position.y + recA.height > recB.position.y) {
        return true;
    }

    return false;
    /*
    bool xOverlap = false;
    bool yOverlap = false;

    //TODO: Consider a check for unconstrained rects then return false.
    if (recB.width == 0) {
        // Only concerned with yOverlap
    }

    if (recB.height == 0) {
        // Only concerned with xOverlap
    }


    if (recA.position.x < recB.position.x) {
        if (recA.width <= 0) {
            return false;
        } else if (recA.position.x + recA.width > recB.position.x) {
            xOverlap = true;
        }
    } else if (recB.position.x + recB.width > recA.position.x) {
        xOverlap = true;
    } else {
        return false;
    }

    if (recA.position.y < recB.position.y) {
        if (recA.height <= 0) {
            return false;
        } else if (recA.position.y + recA.height > recB.position.y) {
            yOverlap = true;
        }
    } else if (recB.position.y + recB.height > recA.position.y) {
        yOverlap = true;
    } else {
        return false;
    }

    return xOverlap && yOverlap;
    */
}

}; // namespace orgphysics
