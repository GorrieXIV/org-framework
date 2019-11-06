#pragma once

/* Origins Controller ________________________________________________ *
 * The origins controller works by mapping controller/keyboard inputs  *
 * to `eventMaps` which trigger a particular event if a given state    *
 * or conditional is true.                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <functional>

#include "platform.hpp"
#include "display.hpp"
#include "entities.hpp"

// We use std::functions to store events (entity member functions)
// to different user inputs.
using Event = std::function<void()>;

class Controller
{
public:

    ///
    Controller();

    ///
    ~Controller() = default;

    /// Reads the current state as reported by SDL
    /// and maps the state to the appropriate event.
    void pollForInput();

    /// Ties clicking of a particular game object to an event
    void addEventOnClick(Entity& object,
                         const std::function<void()> conditional,
                         const std::function<void()> event);

    void addEventOnDragOver();

    /// Creates a listener on mouse click
    /// @param mouseButton: specifies the mouse button to listen on
    /// @param clickType: specifies the click type to listen on
    /// @param eventMap: maps an entity or state to an event
    void addMouseListener(int mouseButton, int clickType, Event event);

    /// Creates a listener on a keystroke
    /// @param mouseButton: specifies the mouse button to listen on
    /// @param clickType: specifies the click type to listen on
    /// @param eventMap: maps an entity or state to an event
    void addKeyListener(int key, int strokeType, int event);

private:
    std::map<int, Event> _mouseEventMap{};
    std::map<int, Event> _keyEventMap{};
};
