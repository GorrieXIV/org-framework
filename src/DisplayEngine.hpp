#pragma once

#include "SDL.h"
#include "Window.hpp"
#include "Vectors.hpp"
#include "Geometry.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

typedef enum {
  ENGINE_SUCCESS,
  ENGINE_FILE_NOT_FOUND,
  ENGINE_SDL_INIT_ERROR,
  ENGINE_RENDERER_ERROR,
  ENGINE_WINDOW_ERROR,
  ENGINE_IMAGE_INIT_ERROR,
  ENGINE_TTF_INIT_ERROR,
  ENGINE_UNKNOWN_ERROR
} DISPLAY_ENGINE_STATUS;

using namespace orgmath;

using Sprite = SDL_Surface;
using HardwareTexture = SDL_Texture*;
using DisplayRectangle = Rectangle<int>;

enum class ImageBufferType { TEXTURE, SURFACE };

class Texture;
class TextTexture;

extern Camera camera;

class DisplayEngine {

  public:
    ///
    DisplayEngine();

    ///
    ~DisplayEngine();

    /// Start SDL.
    DISPLAY_ENGINE_STATUS initSDL();

    /// Load SPRITE sheet <sheetName> from <sheetFile>
    DISPLAY_ENGINE_STATUS loadSpriteSheetFromFile(std::string sheetName, std::string sheetFile);

    /// Load TEXTURE sheet <sheetName> from <sheetFile>
    DISPLAY_ENGINE_STATUS loadTextureSheetFromFile(std::string sheetName, std::string sheetFile);

    ///
    DISPLAY_ENGINE_STATUS setTextureClips();

    ///
    DISPLAY_ENGINE_STATUS clearScreen();

    ///
    DISPLAY_ENGINE_STATUS renderScene();

    /* Drawing */

    /// Draws the clipQuad subset of texture at drawQuad.
    DISPLAY_ENGINE_STATUS drawTextureAt(SDL_Texture* texture,
                                        const DisplayRectangle& clipQuad,
                                        const DisplayRectangle& drawQuad);

    DISPLAY_ENGINE_STATUS drawTextureAt(const std::string& textureSheet,
                                        const DisplayRectangle& clipQuad,
                                        const DisplayRectangle& drawQuad);

    DISPLAY_ENGINE_STATUS drawSpriteAt(const std::string& spriteSheet,
                                       const DisplayRectangle& clipQuad,
                                       const DisplayRectangle& drawQuad);

    /// Draws a filled-in rectangle `rect` in colour `colour`
    DISPLAY_ENGINE_STATUS drawRectangle(const DisplayRectangle& rect,
                                        const std::string& colour = "red");

    /// Copies the content of a region of a stored sprite sheet to `out`.
    /// [ CURRENTLY BROKEN ]
    DISPLAY_ENGINE_STATUS copySpriteFromSheet(SDL_Texture* out,
                                              const std::string& sheetName,
                                              SDL_Rect& clippingWindow) const;

    /// Grants `out` shared access to a particular sprite sheet.
    DISPLAY_ENGINE_STATUS getSpriteFromSheet(SDL_Texture* out,
                                             const std::string& sheetName);

    /// Grants `out` shared access to a particular texture sheet.
    DISPLAY_ENGINE_STATUS getTextureFromSheet(SDL_Texture* out,
                                              const std::string& sheetName);

    /// Adds 'fontIdentiifer' to the list of usable in-game fonts.
    DISPLAY_ENGINE_STATUS loadFontFromFile(const std::string& fontIdentifier,
                                           const std::string& ttfFile,
                                           const int& fontSize = 12);

    TTF_Font* getFont(const std::string& fontIdentifier);

    // Frees memory and stops
    void close();

    //FIXME: Make these private!!
    SDL_Window* window      = NULL;
    SDL_Renderer* renderer  = NULL;

  private:
    /// Initialize the SDL renderer.
    DISPLAY_ENGINE_STATUS initializeRenderer();

    /// Initialize the SDL window.
    DISPLAY_ENGINE_STATUS initializeWindow();

    std::map<std::string, SDL_Surface> _spriteSheets;
    std::map<std::string, SDL_Texture*> _textureSheets;
    std::map<std::string, TTF_Font*> _fonts;
};
