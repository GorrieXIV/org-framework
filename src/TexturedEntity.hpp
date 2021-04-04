#pragma once

#include <vector>

#include "SDL.h"
#include "Entity.hpp"
#include "DisplayEngine.hpp"
#include "Texture.hpp"

typedef enum {
    CENTER,
    TOPLEFT
} RENDER_ANCHOR;

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
                                   const DisplayRectangle& spriteClip);

    /// Share a surface referenced by id found in the sheet JSON.
    void setTextureFromSpriteSheet(const std::string& sheetName,
                                   const std::string& textureId);

    /// Sets a new sprite clip, changing the sprite displayed for the entity.
    void updateSprite(const DisplayRectangle& spriteClip);

    /// Sets a new sprite clip based on a sprite ID in the sheet JSON.
    /// Throws an exception if JSON for this sheet has not been loaded.
    void updateSprite(const std::string& spriteId);

    void createTextureFromSpriteSheet(const std::string& sheetName);

    /// Acquire a clip-copy of a sheet from the display engine.
    //void copyTextureFromSpriteSheet(std::string sheetName)

  protected:
    std::string      _textureSheet{};
    Texture          _texture;
    DisplayRectangle _spriteClip;
    std::string      _spriteId;

    RENDER_ANCHOR _renderAnchor = RENDER_ANCHOR::CENTER;
};
