#include "Texture.hpp"

extern DisplayEngine displayEngine;

Texture::Texture() : _texture(NULL), _width(0), _height(0)
{

}

bool Texture::loadFromFile(std::string path)
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
      printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
      //Color key image
      SDL_SetColorKey(loadedSurface, SDL_TRUE,
                      SDL_MapRGB(loadedSurface->format,
                      0xFF, 0xFF, 0xFF));

      //Create texture from surface pixels
      newTexture = SDL_CreateTextureFromSurface(displayEngine.renderer, loadedSurface);
      if( newTexture == NULL )
      {
        printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
      }
      else
      {
        //Get image dimensions
        _width = loadedSurface->w;
        _height = loadedSurface->h;
      }

      //Get rid of old loaded surface
      SDL_FreeSurface(loadedSurface);
    }

    //Return success
    _texture = newTexture;
    return _texture != NULL;
}


bool Texture::loadFromSheet(const std::string& sheetName)
{
    displayEngine.getTextureFromSheet(_texture, sheetName);
    return _texture != NULL;
}


void Texture::free()
{
    // Free texture if it exists
    if(_texture != NULL) {
        SDL_DestroyTexture(_texture);
        _texture = NULL;
        _width = 0;
        _height = 0;
    }
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    // Modulate texture
    SDL_SetTextureColorMod(_texture, red, green, blue);
}

void Texture::render(const int x, const int y, const Rectangle<int>& clip)
{
    // Set rendering space and render to screen
    Rectangle<int> renderQuad = {x,
                                 y,
                                 static_cast<float>(_width),
                                 static_cast<float>(_height)};

    // Set clip rendering dimensions
    if (!clip.isNull()) {
        renderQuad.width = clip.width;
        renderQuad.height = clip.height;
    }

    displayEngine.drawTextureAt(_texture, clip, renderQuad);
}

FontTexture::FontTexture()
{
}


// Need to include gfont and grenderer in constructor.
bool FontTexture::loadFromRenderedText(TTF_Font *gFont,
                                       std::string text,
                                       SDL_Color textColor,
                                       SDL_Renderer* renderer)
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
    if (textSurface == NULL) {
        printf("Unable to render text surface. SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        _texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (_texture == NULL) {
            printf("Unable to create texture from rendered text. SDL Error: %s\n", SDL_GetError());
        } else {
            _width = textSurface->w;
            _height = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    return _texture != NULL;
}
