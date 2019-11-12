#pragma once

#include "Window.hpp"
#include "Vectors.hpp"

namespace orgmath {

/// Point
struct Point {
    float x = 0;
    float y = 0;

    bool isNull() const {
        return (x == 0 && y == 0);
    }

    std::string toString() const {
        return ("{" + std::to_string(x) + ", " + std::to_string(y) + "}");
    }
}; // Point

constexpr Point ORIGIN{0, 0};


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
    Rectangle(Point topLeft, __type__ width, __type__ height);

    /// Instantiate a rectangle drawn from point topLeft to point bottomRight.
    Rectangle(Point topLeft, Point bottomRight);

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

    __type__ width = 0;
    __type__ height = 0;

    // Position of the top-left corner of the rectangle.
    Point position{nanf(""), nanf("")};
}; // Rectangle

/// Circle
class Circle {
public:
    /// Instantiate a cirlce with an x coordinate, y coordinate, and radius.
    Circle(float x, float y, float radius);

    /// Instantiate a circle with a center-point and radius.
    Circle(Point centerPoint, float radius);

    /// Instantiate an unconstrained circle.
    Circle(float radius);

private:
    Point _center;
    float _radius = 0;
    float _circumference = 0;
}; // Circle

}; // namespace orgmath

template <typename __type__>
bool operator== (const orgmath::Rectangle<__type__>& r1,
                 const orgmath::Rectangle<__type__>& r2);

template <typename __type__>
bool operator!= (const orgmath::Rectangle<__type__>& r1,
                 const orgmath::Rectangle<__type__>& r2);
