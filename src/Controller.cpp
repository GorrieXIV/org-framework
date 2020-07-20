#include "Controller.hpp"

extern Camera camera;

Controller::Controller()
{

}

void Controller::addMouseListener(ORG_MOUSE_INPUT mouseButton,
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
            // Get the screen co-ordinates and convert them to world co-ordinates.
            int x, y;
            SDL_GetMouseState(&x, &y);
            x += camera.position.x;
            y -= camera.position.y;

            try {
                // Map the mouse input to the correct event.
                auto mouseEvent = _mouseEventMap.at(ORG_MOUSE_INPUT::LEFT_CLICK);

                // Execute the event.
                mouseEvent(x, y);
            } catch (std::out_of_range e) { }
        } else if (e.type == SDL_KEYDOWN) {
            try {
                // Map the pressed key (e.key.keysym.sym is the SDL keycode)
                // to the correct event.
                auto keyEvent = _keyEventMap.at(e.key.keysym.sym);

                // Execute the event.
                keyEvent();
            } catch (std::out_of_range e) { }
        }
    }
}
