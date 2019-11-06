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

class Rectangle {
public:
    Rectangle() = default;

    /// Instantiate a rectangle at a specific point.
    Rectangle(float x, float y, float width, float height);

    /// Instantiate a rectangle with topLeft point, width, and height.
    Rectangle(Point topLeft, float width, float height);

    /// Instantiate a rectangle drawn from point topLeft to point bottomRight.
    Rectangle(Point topLeft, Point bottomRight);

    /// Instantiate an unconstrained rectangle.
    Rectangle(float width, float height);

    /// Returns true if 'this' has square dimensions.
    bool isSquare() const;

    /// Returns true if 'this' has zero width, height, x, and y.
    bool isNull() const;

    /// Returns true if 'this' has an unspecified position (x and y = NaN/Inf).
    bool isUnconstrained() const;

    /// Return a string representation of the rectangle.
    /// An unconstrained rectangle should look like
    /// "{Inf, Inf, <width>, <height>}".
    std::string toString() const;

    float width = 0;
    float height = 0;

    // Position of the top-left corner of the rectangle.
    Point position{nanf(""), nanf("")};
}; // Rectangle

const Rectangle NULL_RECTANGLE{0, 0, 0, 0};


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


bool operator== (const orgmath::Rectangle& r1, const orgmath::Rectangle& r2);

bool operator!= (const orgmath::Rectangle& r1, const orgmath::Rectangle& r2);
