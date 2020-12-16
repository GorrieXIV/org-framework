#include "DisplayEngine.hpp"

DisplayEngine::DisplayEngine()
{

}


DisplayEngine::~DisplayEngine()
{
    close();
}


DISPLAY_ENGINE_STATUS DisplayEngine::initWindow(const std::string windowTitle) {
    // Initialization flag
    DISPLAY_ENGINE_STATUS retStatus = ENGINE_SUCCESS;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        retStatus = ENGINE_SDL_INIT_ERROR;
    } else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) { //Set texture filtering to linear
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        // Create window
        window = SDL_CreateWindow(windowTitle.c_str(),
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH,
                                  SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if (window == NULL) {
            std::cout << "Window could not be created! " << SDL_GetError() << std::endl;
            retStatus = ENGINE_WINDOW_ERROR;
        } else {
            // Create renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                std::cout << "Renderer could not be created! SDL Error: "
                          << SDL_GetError() << std::endl;
                retStatus = ENGINE_RENDERER_ERROR;
            } else {
                // Initialize renderer color
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    std::cout << "SDL_image could not initialize! SDL_image Error: "
                              << IMG_GetError() << std::endl;
                    retStatus = ENGINE_IMAGE_INIT_ERROR;
                }

                // Initialize TFF font support.
                if (TTF_Init() == -1) {
                    std::cout << "SDL_ttf could not initialize. SDL_ttf Error: "
                              << TTF_GetError() << std::endl;
                    retStatus = ENGINE_TTF_INIT_ERROR;
                }

                // Initialize SDL_mixer for audio mixing.
                if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    std::cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n"
                              << Mix_GetError() << std::endl;
                    retStatus = ENGINE_UNKNOWN_ERROR;
                }

                // Set the render blend mode to alpha blending.
                if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) < 0) {
                    std::cout << "Error setting SDL blend mode. SDL Error: " << SDL_GetError();
                    retStatus = ENGINE_UNKNOWN_ERROR;
                }
            }
        }
    }

    return retStatus;
}


DISPLAY_ENGINE_STATUS DisplayEngine::initializeRenderer()
{
    std::cout << "WARNING: initializeRenderer not yet implemented." << std::endl;
    return ENGINE_UNKNOWN_ERROR;
}


DISPLAY_ENGINE_STATUS DisplayEngine::initializeWindow()
{
    std::cout << "WARNING: initializeWindow not yet implemented." << std::endl;
    return ENGINE_UNKNOWN_ERROR;
}


DISPLAY_ENGINE_STATUS DisplayEngine::clearScreen()
{
    //FIXME: What sort of error codes does this SDL function return?
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    return ENGINE_SUCCESS;
}

DISPLAY_ENGINE_STATUS DisplayEngine::renderScene()
{
    //FIXME: What sort of error codes does this SDL function return?
    SDL_RenderPresent(renderer);
    return ENGINE_SUCCESS;
}


DISPLAY_ENGINE_STATUS DisplayEngine::loadSpriteSheetFromFile(std::string sheetName,
                                                             std::string sheetFile)
{
    SDL_Surface* sheetSurface = IMG_Load(sheetFile.c_str());
    if (sheetSurface == NULL) {
        std::cout << "Unable to load image " << sheetFile
                  << "! SDL_image Error: " << IMG_GetError() << "\n";
        return ENGINE_FILE_NOT_FOUND;
    } else {
        // Set color key image of the sheet to white.
        SDL_SetColorKey(sheetSurface, SDL_TRUE,
                        SDL_MapRGB(sheetSurface->format, 0xFF, 0xFF, 0xFF));
    }

    _spriteSheets.emplace(sheetName, *sheetSurface);

    return ENGINE_SUCCESS;
}

DISPLAY_ENGINE_STATUS DisplayEngine::loadTextureSheetFromFile(std::string sheetName,
                                                              std::string sheetFile,
                                                              std::string sheetJsonFile)
{
    SDL_Surface* spriteSheet = IMG_Load(sheetFile.c_str());
    if (spriteSheet == NULL) {
        std::cout << "Unable to load image " << sheetFile
                  << "! SDL_image Error: " << IMG_GetError() << "\n";
        return ENGINE_FILE_NOT_FOUND;
    } else {
        // Set color key image of the sheet to white.
        SDL_SetColorKey(spriteSheet, SDL_TRUE,
                        SDL_MapRGB(spriteSheet->format,
                        0xFF, 0xFF, 0xFF));
    }

    SDL_Texture* textureSheet = SDL_CreateTextureFromSurface(renderer, spriteSheet);
    _textureSheets.emplace(sheetName, textureSheet);

    if (sheetJsonFile != "") {
        try {
            std::ifstream jsonStream(sheetJsonFile);
            auto sheetDescriptionJson = json::parse(jsonStream);
            _textureSheetDescriptions.emplace(sheetName, sheetDescriptionJson);
        } catch (...) {
            return ENGINE_UNKNOWN_ERROR;
        }
    }

    return ENGINE_SUCCESS;
}


DISPLAY_ENGINE_STATUS DisplayEngine::setTextureClips()
{
    return ENGINE_SUCCESS;
}

// THE drawTextureAt FUNCTIONS NEED TO BE REFACTORED
DISPLAY_ENGINE_STATUS DisplayEngine::drawTextureAt(SDL_Texture* texture,
                                                   const DisplayRectangle& clipQuad,
                                                   const DisplayRectangle& drawQuad)
{
    try {
        SDL_Rect t1 = {static_cast<int>(clipQuad.position.x),
                       static_cast<int>(clipQuad.position.y),
                       static_cast<int>(clipQuad.width),
                       static_cast<int>(clipQuad.height)};
        SDL_Rect* clipCopy = &t1;
        if (clipQuad.isNull()) { clipCopy = NULL; }

        SDL_Rect t2 = {static_cast<int>(drawQuad.position.x),
                       static_cast<int>(drawQuad.position.y),
                       static_cast<int>(drawQuad.width),
                       static_cast<int>(drawQuad.height)};
        SDL_Rect* drawCopy = &t2;
        if (drawQuad.isNull()) { drawCopy = NULL; }

        drawCopy->x -= (drawQuad.width / 2 + camera.position.x);
        drawCopy->y += (camera.position.y - drawQuad.height / 2);

        SDL_RenderCopy(renderer,
                       texture,
                       clipCopy,
                       drawCopy);

        return ENGINE_SUCCESS;
    } catch (...) {
        return ENGINE_FILE_NOT_FOUND;
    }
}

// THE drawTextureAt FUNCTIONS NEED TO BE REFACTORED
DISPLAY_ENGINE_STATUS DisplayEngine::drawTextureAt(const std::string& sheetName,
                                                   const DisplayRectangle& clipQuad,
                                                   const DisplayRectangle& drawQuad)
{
    try {
        SDL_Rect t1 = {static_cast<int>(clipQuad.position.x),
                       static_cast<int>(clipQuad.position.y),
                       static_cast<int>(clipQuad.width),
                       static_cast<int>(clipQuad.height)};
        SDL_Rect* clipCopy = &t1;
        if (clipQuad.isNull()) { clipCopy = NULL; }

        SDL_Rect t2 = {static_cast<int>(drawQuad.position.x),
                       static_cast<int>(drawQuad.position.y),
                       static_cast<int>(drawQuad.width),
                       static_cast<int>(drawQuad.height)};
        SDL_Rect* drawCopy = &t2;
        if (drawQuad.isNull()) { drawCopy = NULL; }

        drawCopy->x -= (drawQuad.width / 2 + camera.position.x);
        drawCopy->y += (camera.position.y - drawQuad.height / 2);

        SDL_RenderCopy(renderer,
                       _textureSheets.at(sheetName),
                       clipCopy,
                       drawCopy);

        return ENGINE_SUCCESS;
    } catch (...) {
        return ENGINE_FILE_NOT_FOUND;
    }
}

DISPLAY_ENGINE_STATUS DisplayEngine::drawSpriteAt(const std::string& sheetName,
                                                  const DisplayRectangle& clipQuad,
                                                  const DisplayRectangle& drawQuad)
{
    try {
        SDL_Texture* sheetCopy =
            SDL_CreateTextureFromSurface(renderer, &_spriteSheets.at(sheetName));

        SDL_Rect t1 = {static_cast<int>(clipQuad.position.x),
                       static_cast<int>(clipQuad.position.y),
                       static_cast<int>(clipQuad.width),
                       static_cast<int>(clipQuad.height)};
        SDL_Rect* clipCopy = &t1;
        if (clipQuad.isNull()) { clipCopy = NULL; }

        SDL_Rect t2 = {static_cast<int>(drawQuad.position.x),
                       static_cast<int>(drawQuad.position.y),
                       static_cast<int>(drawQuad.width),
                       static_cast<int>(drawQuad.height)};
        SDL_Rect* drawCopy = &t2;
        if (drawQuad.isNull()) { drawCopy = NULL; }

        drawCopy->x -= camera.position.x;
        drawCopy->y += camera.position.y;

        SDL_RenderCopy(renderer, sheetCopy, clipCopy, drawCopy);

        return ENGINE_SUCCESS;
    } catch (...) {
        return ENGINE_FILE_NOT_FOUND;
    }
}

DISPLAY_ENGINE_STATUS DisplayEngine::drawRectangle(const DisplayRectangle& rect,
                                                   const std::string& colour)
{
    if (rect.isUnconstrained()) { return DISPLAY_ENGINE_STATUS::ENGINE_SUCCESS; }

    SDL_Rect rectCopy = {static_cast<int>(rect.position.x - camera.position.x),
                         static_cast<int>(rect.position.y + camera.position.y),
                         static_cast<int>(rect.width),
                         static_cast<int>(rect.height)};

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x77);
    SDL_RenderFillRect(renderer, &rectCopy);

    return DISPLAY_ENGINE_STATUS::ENGINE_SUCCESS;
}

// Texture Clip Cloning approach.
DISPLAY_ENGINE_STATUS DisplayEngine::copySpriteFromSheet(SDL_Texture* out,
                                                         const std::string& sheetName,
                                                         SDL_Rect& clippingWindow) const
{
    SDL_Surface* croppedSheet = NULL;
    SDL_Surface sheetCopy = _spriteSheets.at(sheetName);
    bool nullWindow = clippingWindow.x == 0
                      && clippingWindow.y == 0
                      && clippingWindow.w == 0
                      && clippingWindow.h == 0;
    const SDL_Rect* clipPointer = nullWindow ? NULL : &clippingWindow;
    SDL_BlitSurface(&sheetCopy, clipPointer, croppedSheet, NULL);

    out = SDL_CreateTextureFromSurface(renderer, croppedSheet);

    return ENGINE_SUCCESS;
}

// Sprite cloning approach.
DISPLAY_ENGINE_STATUS DisplayEngine::getSpriteFromSheet(SDL_Texture* out,
                                                        const std::string& sheetName)
{
    SDL_Surface sheetCopy = _spriteSheets.at(sheetName);
    out = SDL_CreateTextureFromSurface(renderer, &sheetCopy);
    return ENGINE_SUCCESS;
}

// Texture cloning approach.
DISPLAY_ENGINE_STATUS DisplayEngine::getTextureFromSheet(SDL_Texture* out,
                                                         const std::string& sheetName)
{
    out = _textureSheets.at(sheetName);
    return ENGINE_SUCCESS;
}

// Load a font into _fonts. fontSize defaults to 12 if none is given.
DISPLAY_ENGINE_STATUS DisplayEngine::loadFontFromFile(const std::string& fontIdentifier,
                                                      const std::string& ttfFile,
                                                      const int& fontSize)
{
    TTF_Font* newFont = TTF_OpenFont(ttfFile.c_str(), fontSize);
    if (newFont == NULL) {
        std::cout << "FAILED TO LOAD TEST FONT" << std::endl;
        return ENGINE_TTF_INIT_ERROR;
    }

    _fonts.emplace(fontIdentifier, newFont);

    return ENGINE_SUCCESS;
}

TTF_Font* DisplayEngine::getFont(const std::string& fontIdentifier)
{
    return _fonts.at(fontIdentifier);
}

DisplayRectangle DisplayEngine::getTextureClipById(const std::string& sheetName,
                                                   const std::string& spriteId)
{
    try {
        auto sheetDescription = _textureSheetDescriptions.at(sheetName);
        auto spriteDetails = sheetDescription["textures"][spriteId];
        return {spriteDetails["x_start"],
                spriteDetails["y_start"],
                spriteDetails["width"],
                spriteDetails["height"]};
    } catch (...) {
        //FIXME: Implement explicit error handling.
        throw std::runtime_error("Sheet matching '" + sheetName + "' not found.");
    }


}

void DisplayEngine::close()
{
    // Destroy window.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;


    // Destroy all texture sheets.
    for (const auto& idSheetPair : _textureSheets) {
        SDL_Texture* sheet = idSheetPair.second;
        if (sheet != NULL) {
            SDL_DestroyTexture(sheet);
            sheet = NULL;
        }
    }

    // Destroy all loaded fonts.
    for (const auto& idFontPair : _fonts) {
        TTF_Font* font = idFontPair.second;
        if (font != NULL) {
            TTF_CloseFont(font);
            font = NULL;
        }
    }


    // Quit SDL subsystems.
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

DISPLAY_ENGINE_STATUS DisplayEngine::setMouseCursor(const std::string& imageFile)
{
    auto cursorImage = IMG_Load(imageFile.c_str());
    int hx = 8; int hy = 8;
    int w, x, y;
    Uint8 *data, *mask, *d, *m, r, g, b;
    Uint32 color;

    w = (cursorImage->w + 7) / 8;
    data = (Uint8*)alloca(w * cursorImage->h * 2);

    if (data == NULL) { return DISPLAY_ENGINE_STATUS::ENGINE_UNKNOWN_ERROR; }

    memset(data, 0, w * cursorImage->h * 2);
    mask = data + w * cursorImage->h;
    if (SDL_MUSTLOCK(cursorImage)) { SDL_LockSurface(cursorImage); }

    for (y = 0; y < cursorImage->h; y++) {
        d = data + y * w;
        m = mask + y * w;
        for (x = 0; x < cursorImage->w; x++) {
            color = getSurfacePixel(cursorImage, x, y);

            Uint32 colorKey = SDL_MapRGB(cursorImage->format, 0xFF, 0xFF, 0xFF);
            if (color != colorKey) {
                SDL_GetRGB(color, cursorImage->format, &r, &g, &b);
                color = (r + g + b) / 3;
                m[x / 8] |= 128 >> (x & 7);
                if (color < 128) { d[x / 8] |= 128 >> (x & 7); }
            }
        }
    }

    // Unlock cursor image if necessary.
    if (SDL_MUSTLOCK(cursorImage)) { SDL_UnlockSurface(cursorImage); }

    // Finally, create the SDL cursor and set it.
    customCursor = SDL_CreateCursor(data, mask, w, cursorImage->h, 0, 0);
    SDL_SetCursor(customCursor);
}

Uint32 DisplayEngine::getSurfacePixel(SDL_Surface* surface, int x, int y) const
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
    case 1:
        return *p;
        break;
    case 2:
        return *(Uint16 *)p;
        break;
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            return p[0] << 16 | p[1] << 8 | p[2]; }
        else {
            return p[0] | p[1] << 8 | p[2] << 16;
        }
        break;
    case 4:
        return *(Uint32 *)p;
        break;
    default:
        return 0;
    }
}
