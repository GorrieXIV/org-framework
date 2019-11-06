#pragma once

#include "platform.hpp"

#include "DisplayEngine.hpp"

class Animation {
  public:
    Animation(std::vector<SDL_Rect> frameClips);

  private:
    std::vector<SDL_Rect> _clips{};
};
