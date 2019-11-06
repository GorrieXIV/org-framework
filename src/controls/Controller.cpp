#include "Controller.hpp"

extern Camera camera;

Controller::Controller()
{

}

void Controller::addMouseListener(int mouseButton, int clickType, Event event)
{
    _mouseEventMap.emplace(mouseButton, event);
}

void Controller::addKeyListener(int key, int strokeType, int eventMap)
{

}

void Controller::pollForInput()
{
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0) {
        if(e.type == SDL_QUIT) {
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            x += camera.position.x;
            y -= camera.position.y;
            auto thing = _mouseEventMap.at(SDL_MOUSEBUTTONDOWN);
            // thing();
        } else if (e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
            case SDLK_q:
                break;
            case SDLK_LEFT:
                break;
            case SDLK_RIGHT:
                break;
            case SDLK_DOWN:
                break;
            case SDLK_UP:
                break;
            default:
                break;
            }
        }
    }
}
