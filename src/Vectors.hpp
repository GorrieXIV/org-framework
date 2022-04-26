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

    Vector2& operator+=(const Vector2& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
};
