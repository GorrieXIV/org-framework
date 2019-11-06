#pragma once

#include "platform.hpp"
#include "entities.hpp"

#include "DisplayEngine.hpp"
#include "Texture.hpp"

/* * * * * * * * * * * * * * * *
 * *  TEXTURED ENTITY CLASS  * *
 * * * * * * * * * * * * * * * */
class TexturedEntity : public Entity {
  public:

    /// Constructor.
    TexturedEntity();

    /// Destructor.
    ~TexturedEntity();

    /// Render the entity.
    void render(bool debug_worldPosition = false, bool debug_hitboxes = false);

    /// Share a surface owned by the display engine.
    void setTextureFromSpriteSheet(const std::string& sheetName,
                                   const Rectangle& spriteClip);

    /// Sets a new sprite clip, changing the sprite displayed for the entity.
    void updateSprite(const Rectangle& spriteClip);

    void createTextureFromSpriteSheet(const std::string& sheetName);

    /// Acquire a clip-copy of a sheet from the display engine.
    //void copyTextureFromSpriteSheet(std::string sheetName)

  protected:
    std::string _textureSheet{};
    Texture _texture;
    Rectangle _spriteClip;
};
