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

using Vector2 = vec2_f32;
