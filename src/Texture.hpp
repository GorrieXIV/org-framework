#pragma once

#include <string>

#include "SDL.h"
#include "Geometry.hpp"
#include "DisplayEngine.hpp"

class DisplayEngine;
extern DisplayEngine displayEngine;

using namespace orgmath;

using DisplayRectangle = Rectangle<int>;

class Texture {
  public:
    /// Initializes variables
    Texture();

    /// Deallocates memory
    ~Texture() { free(); }

    /// Loads image at specified path
    bool loadFromFile(std::string path);

    /// Specify a sprite from a given sprite sheet.
    bool loadFromSheet(const std::string& sheetName);

    /// Deallocates texture
    void free();

    /// Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    void setBlendMode(SDL_BlendMode blending);

    void setAlpha (Uint8 alpha);

    /// Renders texture at given point
    void render(const int x, const int y, const DisplayRectangle& clip);

    /// Gets image dimensions
    void setWidth(int width) { _width = width; }
    void setHeight(int height) { _height= height; }
    int getWidth() const { return _width; }
    int getHeight() const { return _height; }

  protected:
    /// The actual hardware texture
    SDL_Texture* _texture;

    /// Image dimensions
    int _width;
    int _height;
};

class Surface {
  public:
    Surface();
};

class FontTexture : public Texture {
  public:

    /// Initialize object.
    FontTexture();

    /// Load a string texture to be displayed.
    ///@param: object specifying the font type
    ///@param: string of text
    ///@param: color of text
    ///@param: sdl renderer
    bool loadFromRenderedText(TTF_Font* gFont,
                              std::string text,
                              SDL_Color textColor,
                              SDL_Renderer* renderer);
};
