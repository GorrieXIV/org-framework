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
    // Check mouse state and trigger events.
    int x = 0;
    int y = 0;
    if (SDL_GetMouseState(&x, &y) && SDL_BUTTON(SDL_BUTTON_LEFT)) {
        x += camera.position.x;
        y -= camera.position.y;
        try {
            // Map the mouse input to the correct event.
            auto mouseEvent = _mouseEventMap.at(ORG_MOUSE_INPUT::LEFT_CLICK);

            // Execute the event.
            mouseEvent(x, y);
        } catch (std::out_of_range e) { }
    }

    /// Check keyboard state and trigger events.
    auto keyboardState = SDL_GetKeyboardState(0);
    for (const auto& [keycode, event] : _keyEventMap) {
        if (keyboardState[keycode]) {
            event();
        }
    }
}
