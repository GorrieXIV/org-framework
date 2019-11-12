#pragma once

#include "platform.hpp"
#include "math.hpp"

using namespace orgmath;

namespace orgphysics {

bool collisionDetected(const Rectangle<float>& recA, const Rectangle<float>& recB);

}; // namespace orgphysics
