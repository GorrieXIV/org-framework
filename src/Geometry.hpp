#pragma once

#include <string>

#include "SDL.h"
#include "Window.hpp"
#include "Vectors.hpp"

namespace orgmath {

/// Point
template <typename __type__>
struct Point {
    __type__ x = 0;
    __type__ y = 0;

    bool isNull() const {
        return (x == 0 && y == 0);
    }

    std::string toString() const {
        return ("{" + std::to_string(x) + ", " + std::to_string(y) + "}");
    }
}; // Point

/// Rectangle
template <typename __type__>
class Rectangle {
public:
    Rectangle() = default;

    /// Instantiate a rectangle at a specific point.
    Rectangle(__type__ x, __type__ y, __type__ width, __type__ height)
    : width{width}
    , height{height}
    , position{x, y}
    {
        // Void
    }

    /// Instantiate a rectangle with topLeft point, width, and height.
    Rectangle(Point<__type__> topLeft, __type__ width, __type__ height);

    /// Instantiate a rectangle drawn from point topLeft to point bottomRight.
    Rectangle(Point<__type__> topLeft, Point<__type__> bottomRight);

    /// Instantiate an unconstrained rectangle.
    Rectangle(__type__ width, __type__ height)
    : width{width}
    , height{height}
    {
        // Void
    }

    /// Returns true if 'this' has square dimensions.
    bool isSquare() const
    {
        return (width == height);
    }

    /// Returns true if 'this' has zero width, height, x, and y.
    bool isNull() const
    {
        return (position.isNull() && width == 0 && height == 0);
    }

    /// Returns true if 'this' has an unspecified position (x and y = NaN/Inf).
    bool isUnconstrained() const
    {
        return (position.x == nanf("") && position.y == nanf(""));
    }

    /// Return a string representation of the rectangle.
    /// An unconstrained rectangle should look like
    /// "{Inf, Inf, <width>, <height>}".
    std::string toString() const;

    __type__ width{};
    __type__ height{};

    // Position of the top-left corner of the rectangle.
    //TODO: Readd support for initializing position as a pair of NaNs.
    Point<__type__> position{{}, {}};
}; // Rectangle

/// Circle
template<typename __type__>
class Circle {
public:
    /// Instantiate a cirlce with an x coordinate, y coordinate, and radius.
    Circle(__type__ x, __type__ y, __type__ radius);

    /// Instantiate a circle with a center-point and radius.
    Circle(Point<__type__> centerPoint, __type__ radius);

    /// Instantiate an unconstrained circle.
    Circle(__type__ radius);

private:
    Point<__type__> _center;
    __type__ _radius = 0;
    __type__ _circumference = 0;
}; // Circle

template <typename __type__>
class Triangle {
public:
    Triangle() = default;

    /// Instantiate a rectangle at a specific point.
    Triangle(std::vector<__type__> vertices)
    : vertices{vertices}
    {
        // Void.
    }

    /// Return a string representation of the rectangle.
    /// An unconstrained rectangle should look like
    /// "{Inf, Inf, <width>, <height>}".
    std::string toString() const;

    // Vector of points representing the vertices of the shape.
    std::vector<__type__> vertices{};
}; // Triangle

}; // namespace orgmath

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
