#include "Geometry.hpp"

bool operator== (const orgmath::Rectangle& r1, const orgmath::Rectangle& r2) {
    return ((r1.position.x == r2.position.x)
             && (r1.position.y == r2.position.y)
             && (r1.width == r2.width)
             && (r1.height == r2.height));
}

bool operator!= (const orgmath::Rectangle& r1, const orgmath::Rectangle& r2) {
    return ((r1.position.x != r2.position.x)
             || (r1.position.y != r2.position.y)
             || (r1.width != r2.width)
             || (r1.height != r2.height));
}

namespace orgmath {

Rectangle::Rectangle(float x, float y, float w, float h)
: width{w}
, height{h}
, position{x, y}
{

}

Rectangle::Rectangle(float w, float h)
: width{w}
, height{h}
{

}

bool Rectangle::isSquare() const
{
    return (width == height);
}

bool Rectangle::isNull() const
{
    return (position.isNull() && width == 0 && height == 0);
}

bool Rectangle::isUnconstrained() const
{
    return (position.x == nanf("") && position.y == nanf(""));
}

}; // namespace orgmath
