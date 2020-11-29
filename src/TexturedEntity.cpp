#include "TexturedEntity.hpp"

extern DisplayEngine displayEngine;

TexturedEntity::TexturedEntity() {}

TexturedEntity::~TexturedEntity() {}

void TexturedEntity::render(bool debug_worldPosition, bool debug_hitboxes)
{
    if (_spriteClip.isNull()) {
        return;
    }
    DisplayRectangle drawQuad = DisplayRectangle(static_cast<int>(_position.x),
                                                 static_cast<int>(_position.y),
                                                 static_cast<int>(_width),
                                                 static_cast<int>(_height));
    displayEngine.drawTextureAt(_textureSheet, _spriteClip, drawQuad);

    if (debug_worldPosition) {
        std::string entityPosition = "[" + std::to_string(_position.x)
                                   + "," + std::to_string(_position.y) + "]";
        FontTexture positionLabel = FontTexture();
        try {
            positionLabel.loadFromRenderedText(displayEngine.getFont("lazy"),
                                               entityPosition,
                                               {0xFF, 0xFF, 0xFF},
                                               displayEngine.renderer);

            positionLabel.render(static_cast<int>(_position.x - _width / 2),
                                 static_cast<int>(_position.y - _height / 2),
                                 {0, 0, 0, 0});
        } catch (...) {
            std::cout << "WARNING: Tried to print with an uninitialized font." << std::endl;
            return;
        }
    }

    if (debug_hitboxes) {
        for (const auto& hitbox : _hitboxes) {
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
