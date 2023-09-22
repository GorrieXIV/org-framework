#include "TexturedEntity.hpp"

extern DisplayEngine displayEngine;

TexturedEntity::TexturedEntity() {}

TexturedEntity::~TexturedEntity() {}

void TexturedEntity::render(bool debug_worldPosition, bool debug_hitboxes)
{
    // If the entity has no sprite, and debug rendering isn't being used, simply return.
    if (_spriteClip.isNull() && !(debug_worldPosition || debug_hitboxes)) {
        return;
    }

    // Render the entities sprite.
    DisplayRectangle drawQuad = DisplayRectangle(static_cast<int>(_position.x),
                                                 static_cast<int>(_position.y),
                                                 static_cast<int>(_width),
                                                 static_cast<int>(_height));
    if (_renderAnchor == RENDER_ANCHOR::CENTER) {
        drawQuad.position.x -= _width / 2;
        drawQuad.position.y -= _height / 2;
    }
    displayEngine.drawTextureAt(_textureSheet, _spriteClip, drawQuad, _angle);

    // Draw child textures.
    for (const auto& [texture, quad] : _childTextures) {
        texture->render(_position.x + quad.position.x,
                        _position.y + quad.position.y,
                        {0, 0, 0, 0});
    }

    // Render the entities position coordinates, if requested.
    if (debug_worldPosition) {
        try {
            std::string entityPosition = "[" + std::to_string(_position.x)
                                       + "," + std::to_string(_position.y) + "]";
            FontTexture positionLabel = FontTexture();
            positionLabel.loadFromRenderedText(displayEngine.getFont("retro"),
                                               entityPosition,
                                               {0x00, 0x00, 0xFF},
                                               displayEngine.renderer);

            positionLabel.render(static_cast<int>(_position.x - _width / 2 + 50),
                                 static_cast<int>(_position.y - _height / 2),
                                 {0, 0, 0, 0});
        } catch (...) {
            std::cout << "WARNING: Tried to print with an uninitialized font." << std::endl;
            return;
        }
    }

    try {
        displayEngine.drawPolygon(collider.vertices);
        displayEngine.drawPoint(collider.getPosition());
    } catch(...) {
        // No valid polygon collider, do nothing for now..
    }

    // Render the entities hitboxes, if requested.
    if (debug_hitboxes) {
        for (const auto& [hitbox, isBlocking] : _hitboxes) {
            //TODO: Build a cleaner means of casting between different Rectangle types.
            auto worldPosHitbox = relativeToWorldPos(hitbox);
            auto displayPositionHitbox = Rectangle<int>(static_cast<int>(worldPosHitbox.position.x),
                                                        static_cast<int>(worldPosHitbox.position.y),
                                                        static_cast<int>(worldPosHitbox.width),
                                                        static_cast<int>(worldPosHitbox.height));
            displayEngine.drawRectangle(displayPositionHitbox);
        }
    }
}

void TexturedEntity::setTextureFromSpriteSheet(const std::string& sheetName,
                                               const DisplayRectangle& spriteClip)
{
    _textureSheet = sheetName;
    _spriteClip = spriteClip;
}

void TexturedEntity::setTextureFromSpriteSheet(const std::string& sheetName,
                                               const std::string& textureId)
{
    _textureSheet = sheetName;
    DisplayRectangle spriteClip = displayEngine.getTextureClipById(_textureSheet, textureId);
    _spriteId = textureId;
    _spriteClip = spriteClip;
}

void TexturedEntity::createTextureFromSpriteSheet(const std::string& sheetName)
{
    _spriteClip = DisplayRectangle(0, 0, 0, 0);
    _texture.loadFromSheet(sheetName);
}

void TexturedEntity::updateSprite(const DisplayRectangle& spriteClip)
{
    _spriteClip = spriteClip;
}

void TexturedEntity::updateSprite(const std::string& spriteId)
{
    DisplayRectangle spriteClip = displayEngine.getTextureClipById(_textureSheet, spriteId);
    _spriteId = spriteId;
    _spriteClip = spriteClip;
}
