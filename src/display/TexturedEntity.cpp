#include "TexturedEntity.hpp"

extern DisplayEngine displayEngine;

TexturedEntity::TexturedEntity() {}

TexturedEntity::~TexturedEntity() {}

void TexturedEntity::render(bool debug_worldPosition, bool debug_hitboxes)
{
    if (_spriteClip.isNull()) {
        return;
    }
    Rectangle drawQuad = Rectangle(static_cast<int>(_position.x),
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
            Rectangle worldPosHitbox = relativeToWorldPos(hitbox);
            displayEngine.drawRectangle(worldPosHitbox);
        }
    }
}

void TexturedEntity::setTextureFromSpriteSheet(const std::string& sheetName, const Rectangle& spriteClip)
{
    _textureSheet = sheetName;
    _spriteClip = spriteClip;
}

void TexturedEntity::createTextureFromSpriteSheet(const std::string& sheetName)
{
    _spriteClip = Rectangle(0, 0, 0, 0);
    _texture.loadFromSheet(sheetName);
}

void TexturedEntity::updateSprite(const Rectangle& spriteClip)
{
    _spriteClip = spriteClip;
}
