#pragma once

#include <iostream>
#include "Vectors.hpp"

class LineSegment
{
  public:
    Vector2 start = Vector2::nullVector();
    Vector2 end   = Vector2::nullVector();

    LineSegment(Vector2 startPoint, Vector2 endPoint)
    : start(startPoint)
    , end(endPoint)
    { }

    std::string toString() const
    {
        return "(" + start.toString() + ", " + end.toString() + ")";
    }
};
