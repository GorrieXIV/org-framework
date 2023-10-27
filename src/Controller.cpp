#include "Controller.hpp"

extern Camera camera;

Controller::Controller()
{
    // Get the size of the keystate for this run context, and initialize
    // our stored keystate pointer with that much space.
    std::unique_ptr<int> keyStateSize = std::make_unique<int>();
    SDL_GetKeyboardState(keyStateSize.get());
    _previousKeyState = std::make_unique<uint8_t[]>(*keyStateSize);
}

void Controller::addMouseListener(ORG_MOUSE_INPUT mouseButton,
                                  ORG_MOUSE_EVENT clickType,
                                  MouseEvent event,
                                  int priority)
{
    _mouseEventMap.emplace(mouseButton, event);
}

void Controller::clearMouseListeners(ORG_MOUSE_INPUT mouseButton)
{
    if (mouseButton == ORG_MOUSE_INPUT::VOID) {
        _mouseEventMap.clear();
    } else {
        _mouseEventMap.erase(mouseButton);
    }
}

void Controller::addKeyListener(std::string key,
                                ORG_KEY_EVENT strokeType,
                                KeyEvent event,
                                int priority)
{
    switch (strokeType) {
        case ORG_KEY_EVENT::KEY_DOWN: 
            _keyDownEventMap.emplace(ORG_SDL_KEY_MAPPING.at(key), event);
            break;
        case ORG_KEY_EVENT::KEY_UP: 
            _keyUpEventMap.emplace(ORG_SDL_KEY_MAPPING.at(key), event);
            break;
        default: 
            _keyHoldEventMap.emplace(ORG_SDL_KEY_MAPPING.at(key), event);
            break;
    }

}

void Controller::addEventOnClick(std::shared_ptr<Entity> entityReference,
                                 const ORG_MOUSE_INPUT mouseButton,
                                 MouseEvent event)
{
    if (mouseButton == ORG_MOUSE_INPUT::LEFT_CLICK) {
        _leftClickEventMap.emplace(entityReference, event);
    } else if (mouseButton == ORG_MOUSE_INPUT::RIGHT_CLICK) {
        _rightClickEventMap.emplace(entityReference, event);
    }
}

void Controller::clearClickListeners(ORG_MOUSE_INPUT mouseButton)
{
    if (mouseButton == ORG_MOUSE_INPUT::LEFT_CLICK) {
        _leftClickEventMap.clear();
    } else if (mouseButton == ORG_MOUSE_INPUT::RIGHT_CLICK) {
        _rightClickEventMap.clear();
    } else {
        _leftClickEventMap.clear();
        _rightClickEventMap.clear();
    }
}

void Controller::poll()
{
    SDL_PumpEvents();

    // Check mouse state and trigger events.
    int x = 0;
    int y = 0;
    int mouseButtonState = SDL_GetMouseState(&x, &y);
    x += camera.position.x;
    y -= camera.position.y;

    if (mouseButtonState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        if (!_leftMouseDownTracker) {
            try {
                // Map the mouse input to the correct event.
                auto mouseEvent = _mouseEventMap.at(ORG_MOUSE_INPUT::LEFT_CLICK);

                // Execute the event.
                mouseEvent(x, y);
            } catch (std::out_of_range e) { }

            for (const auto& [entityReference, clickEvent] : _leftClickEventMap) {
                auto entityPosition   = entityReference->getPosition();
                auto entityDimensions = entityReference->getDimensions();
                if (entityPosition.x > x - entityDimensions.x &&
                    entityPosition.x < x + entityDimensions.x &&
                    entityPosition.y > y - entityDimensions.y &&
                    entityPosition.y < y + entityDimensions.y) {
                    clickEvent(x, y);
                }
            }
        }
        _leftMouseDownTracker = true;
    } else {
        _leftMouseDownTracker = false;
    }

    if (mouseButtonState & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        if (!_rightMouseDownTracker) {
            try {
                // Map the mouse input to the correct event.
                auto mouseEvent = _mouseEventMap.at(ORG_MOUSE_INPUT::RIGHT_CLICK);

                // Execute the event.
                mouseEvent(x, y);
            } catch (std::out_of_range e) { }

            for (const auto& [entityReference, clickEvent] : _rightClickEventMap) {
                auto entityPosition   = entityReference->getPosition();
                auto entityDimensions = entityReference->getDimensions();
                if (entityPosition.x > x - entityDimensions.x &&
                    entityPosition.x < x + entityDimensions.x &&
                    entityPosition.y > y - entityDimensions.y &&
                    entityPosition.y < y + entityDimensions.y) {
                    clickEvent(x, y);
                }
            }
        }
        _rightMouseDownTracker = true;
    } else {
        _rightMouseDownTracker = false;
    }

    // Check keyboard state and trigger events.
    std::unique_ptr<int> keyStateSize = std::make_unique<int>();
    auto keyboardState = SDL_GetKeyboardState(keyStateSize.get());
    for (const auto& [keycode, event] : _keyDownEventMap) {
        if (keyboardState[keycode]) {
            event();
        }
    }

    // Check for key up events by checking if key from last frame
    // is no longer being held down.
    for (const auto& [keycode, event] : _keyUpEventMap) {
        if (_previousKeyState[keycode] && !keyboardState[keycode]) {
            event();
        }
    }

    // Check for key hold events by checking if keys have been held across frames.
    for (const auto& [keycode, event] : _keyHoldEventMap) {
        if (_previousKeyState[keycode] && keyboardState[keycode]) {
            event();
        }
    }

    // Copy current frames keyboard state into the previouse key state.
    memcpy(_previousKeyState.get(), keyboardState, *keyStateSize);
}
