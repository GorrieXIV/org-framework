#include "Geometry.hpp"

template <typename __type__>
bool operator== (const orgmath::Rectangle<__type__>& r1,
                 const orgmath::Rectangle<__type__>& r2)
{
    return ((r1.position.x == r2.position.x)
             && (r1.position.y == r2.position.y)
             && (r1.width == r2.width)
             && (r1.height == r2.height));
}

template <typename __type__>
bool operator!= (const orgmath::Rectangle<__type__>& r1,
                 const orgmath::Rectangle<__type__>& r2)
{
    return ((r1.position.x != r2.position.x)
             || (r1.position.y != r2.position.y)
             || (r1.width != r2.width)
             || (r1.height != r2.height));
}
