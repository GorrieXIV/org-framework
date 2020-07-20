#pragma once

#include <vector>

#include "SDL.h"
#include "Vectors.hpp"
#include "Geometry.hpp"

using namespace orgmath;

/* ENTITY CLASS ------------------------------------------- */
class Entity {
  public:

    /// Constructor.
    Entity();

    /// Destructor.
    ~Entity();

    /// Get the entities position as a 2d vector.
    Vector2 getPosition() const { return _position; }

    /// Get the entities width and height as a 2d vector.
    Vector2 getDimensions() const { return {_width, _height}; }

    /// Set the entities position with a 2d vector
    void setPosition(Vector2 position);

    /// Set the entities position with an x and a y coordinate.
    void setPosition(float x, float y);

    void setDimensions(Vector2 dimension);

    void setWidth(float width) { _width = width; }

    void setHeight(float height) { _height = height; }

    Rectangle<float> relativeToWorldPos(const Rectangle<float>& rect);

    Rectangle<float> temp_getHitbox() {
        auto hb = _hitboxes.front();
        return Rectangle<float>(hb.position.x + _position.x - hb.width / 2,
                                hb.position.y + _position.y - hb.height / 2,
                                hb.width,
                                hb.height);
    }

    std::string getStatus() const;

  protected:
    Vector2 _position;
    float _width;
    float _height;

    std::vector<Rectangle<float>> _hitboxes{};

};
