#pragma once

#include <iostream>

typedef struct
{
    int32_t x;
    int32_t y;
} vec2_i32;

typedef struct
{
    float x;
    float y;
} vec2_f32;

class Vector2
{
  public:
    float x = 0.0f;
    float y = 0.0f;

    static Vector2 nullVector()
    {
        return Vector2{0.0f, 0.0f};
    }

    bool isNull() const
    {
        return (x == 0.0f && y == 0.0f);
    }

    std::string toString() const
    {
        return "{" + std::to_string(x) + ", " + std::to_string(y) + "}";
    }

    Vector2& operator+=(const Vector2& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }

    Vector2 operator+(const Vector2& rhs) const
    {
        float newX = this->x + rhs.x;
        float newY = this->y + rhs.y;
        return {newX, newY};
    }

    Vector2 operator-(const Vector2& rhs) const
    {
        float newX = this->x - rhs.x;
        float newY = this->y - rhs.y;
        return {newX, newY};
    }

    // Scalar multiplication by an integer.
    Vector2 operator*(int multiple) const
    {
        return {
            this->x * multiple,
            this->y * multiple
        };
    }

    // Scalar multiplication by a float.
    Vector2 operator*(float multiple) const
    {
        return {
            this->x * multiple,
            this->y * multiple
        };
    }

    // 2-dimensional vector "cross product".
    float operator*(const Vector2& rhs) const
    {
        return (this->x * rhs.y) - (this->y * rhs.x);
    }


};
