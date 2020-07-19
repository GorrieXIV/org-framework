#include "Controller.hpp"

extern Camera camera;

Controller::Controller()
{

}

void Controller::addMouseListener(int mouseButton,
                                  ORG_MOUSE_EVENT clickType,
                                  MouseEvent event,
                                  int priority)
{
    _mouseEventMap.emplace(mouseButton, event);
}

void Controller::addKeyListener(char key,
                                ORG_KEY_EVENT strokeType,
                                KeyEvent event,
                                int priority)
{
    _keyEventMap.emplace(ORG_SDL_KEY_MAPPING.at(key), event);
}

void Controller::poll()
{
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            x += camera.position.x;
            y -= camera.position.y;
            //auto thing = _mouseEventMap.at(SDL_MOUSEBUTTONDOWN);
            // thing();
        } else if (e.type == SDL_KEYDOWN) {
            try {
                // Map the pressed key (e.key.keysym.sym is the SDL keycode)
                // to the correct event.
                std::function<void()> keyEvent = _keyEventMap.at(e.key.keysym.sym);

                // Execute the event.
                keyEvent();
            } catch (std::out_of_range e) { }
        }
    }
}
