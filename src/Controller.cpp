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
    _keyEventMap.emplace(ORG_SDL_KEY_MAPPING.at(key), event);
}

void Controller::addEventOnClick(Entity& entity,
                                 const ORG_MOUSE_INPUT mouseButton,
                                 MouseEvent event)
{
    auto entityReference = EntityReference(&entity);
    std::pair<EntityReference, ORG_MOUSE_INPUT> entityClickPairing{entityReference, mouseButton};
    _clickEventMap.emplace(entityClickPairing, event);
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
        try {
            // Map the mouse input to the correct event.
            auto mouseEvent = _mouseEventMap.at(ORG_MOUSE_INPUT::LEFT_CLICK);

            // Execute the event.
            mouseEvent(x, y);
        } catch (std::out_of_range e) { }

        for (const auto& [entityClickPairing, clickEvent] : _clickEventMap) {
            // Retrieve entity and mouse button from the std::pair.
            auto entityReference = std::get<0>(entityClickPairing);
            auto mouseButton     = std::get<1>(entityClickPairing);

            if (mouseButton != ORG_MOUSE_INPUT::LEFT_CLICK) {
                continue;
            }

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

    if (mouseButtonState & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        try {
            // Map the mouse input to the correct event.
            auto mouseEvent = _mouseEventMap.at(ORG_MOUSE_INPUT::RIGHT_CLICK);

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
