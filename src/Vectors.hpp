/* OrgEngine - vector types
 *
 * Author: Robert "gxiv" Gorrie
 */

#pragma once

typedef struct {
    int32_t x;
    int32_t y;
} vec2_i32;

typedef struct {
    float x;
    float y;
} vec2_f32;

class Vector2 {
  public:
    float x;
    float y;
    bool isNull = false;

    static Vector2 nullVector() {
        return Vector2{0, 0, true};
    }

    Vector2& operator+=(const Vector2& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }

    Vector2 operator+(const Vector2& rhs) {
        float newX = this->x + rhs.x;
        float newY = this->y + rhs.y;
        return {newX, newY};
    }
};
