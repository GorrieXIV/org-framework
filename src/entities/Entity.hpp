#pragma once

#include "platform.hpp"
#include "math.hpp"

using namespace orgmath;

/* ENTITY CLASS ------------------------------------------- */
class Entity {
  public:

    /// Constructor.
    Entity();

    /// Destructor.
    ~Entity();

    /// Get the entities position as a 2d vector.
    Vector2 getPosition() const;

    /// Set the entities position with a 2d vector
    void setPosition(Vector2 position);

    /// Set the entities position with an x and a y coordinate.
    void setPosition(float x, float y);

    void setDimensions(Vector2 dimension);

    void setWidth(float width) { _width = width; }

    void setHeight(float height) { _height = height; }

    Rectangle relativeToWorldPos(const Rectangle& rect);

    Rectangle temp_getHitbox() {
        auto hb = _hitboxes.front();
        return Rectangle(hb.position.x + _position.x - hb.width / 2,
                         hb.position.y + _position.y - hb.height / 2,
                         hb.width,
                         hb.height);
    }

    std::string getStatus() const;

  protected:
    Vector2 _position;
    float _width;
    float _height;

    std::vector<Rectangle> _hitboxes{};

};
