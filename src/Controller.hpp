#pragma once

/* Origins Controller ________________________________________________ *
 * The origins controller works by mapping controller/keyboard inputs  *
 * to `eventMaps` which trigger a particular event if a given state    *
 * or conditional is true.                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <functional>
#include <map>
#include <memory>

#include "SDL.h"
#include "Camera.hpp"
#include "Entity.hpp"

typedef enum {
    MOUSE_DOWN, // 0x00
    MOUSE_HOLD, // 0x01
    MOUSE_UP,   // 0x02
} ORG_MOUSE_EVENT;

typedef enum {
    VOID,        // 0x00
    LEFT_CLICK,  // 0x01
    RIGHT_CLICK, // 0x02
} ORG_MOUSE_INPUT;

typedef enum {
    KEY_DOWN, // 0x00
    KEY_HOLD, // 0x01
    KEY_UP,   // 0x02
} ORG_KEY_EVENT;

const std::map<std::string, int> ORG_SDL_KEY_MAPPING = {
    {"a", SDL_SCANCODE_A},
    {"b", SDL_SCANCODE_B},
    {"c", SDL_SCANCODE_C},
    {"d", SDL_SCANCODE_D},
    {"e", SDL_SCANCODE_E},
    {"f", SDL_SCANCODE_F},
    {"g", SDL_SCANCODE_G},
    {"h", SDL_SCANCODE_H},
    {"i", SDL_SCANCODE_I},
    {"j", SDL_SCANCODE_J},
    {"k", SDL_SCANCODE_K},
    {"l", SDL_SCANCODE_L},
    {"m", SDL_SCANCODE_M},
    {"n", SDL_SCANCODE_N},
    {"o", SDL_SCANCODE_O},
    {"p", SDL_SCANCODE_P},
    {"q", SDL_SCANCODE_Q},
    {"r", SDL_SCANCODE_R},
    {"s", SDL_SCANCODE_S},
    {"t", SDL_SCANCODE_T},
    {"u", SDL_SCANCODE_U},
    {"v", SDL_SCANCODE_V},
    {"w", SDL_SCANCODE_W},
    {"x", SDL_SCANCODE_X},
    {"y", SDL_SCANCODE_Y},
    {"z", SDL_SCANCODE_Z},
    {"UP", SDL_SCANCODE_UP},
    {"RIGHT", SDL_SCANCODE_RIGHT},
    {"DOWN", SDL_SCANCODE_DOWN},
    {"LEFT", SDL_SCANCODE_LEFT},
    {"SPACE", SDL_SCANCODE_SPACE}
};

// We use std::functions to store events (entity member functions)
// to different user inputs.
using MouseEvent      = std::function<void(int, int)>;
using KeyEvent        = std::function<void()>;
using EntityReference = std::shared_ptr<Entity>;

class Controller
{
  public:

    ///
    Controller();

    ///
    ~Controller() = default;

    /// Reads the current state as reported by SDL
    /// and cycls through event maps to fire the appropriate events.
    void poll();

    /// Ties clicking of a particular game object to an event
    void addEventOnClick(std::shared_ptr<Entity> entity,
                         const ORG_MOUSE_INPUT mouseButton,
                         MouseEvent event);

    void addEventOnDragOver();

    void clearClickListeners(ORG_MOUSE_INPUT mouseButton = ORG_MOUSE_INPUT::VOID);

    /// Creates a listener on mouse click
    /// @param mouseButton: specifies the mouse button to listen on
    /// @param clickType:   specifies the click type to listen on
    /// @param eventMap:    maps an entity or state to an event
    /// @param priority:    used to set the order of event firing.
    ///                     smaller values for priority fire before higher values,
    ///                     negative priority events will never fire.
    void addMouseListener(ORG_MOUSE_INPUT mouseButton,
                          ORG_MOUSE_EVENT clickType,
                          MouseEvent event,
                          int priority);

    /// Creates a listener on mouse click
    /// @param mouseButton: specifies the type of listeners/events to clear.
    ///                     if NULL, all mouse events will be removed.
    void clearMouseListeners(ORG_MOUSE_INPUT mouseButton = ORG_MOUSE_INPUT::VOID);

    /// Creates a listener on a keystroke
    /// @param mouseButton: specifies the mouse button to listen on
    /// @param clickType:   specifies the click type to listen on
    /// @param event:       maps an entity or state to an event
    /// @param priority:    used to set the order of event firing.
    ///                     smaller values for priority fire before higher values,
    ///                     negative priority events will never fire.
    void addKeyListener(std::string key,
                        ORG_KEY_EVENT strokeType,
                        KeyEvent event,
                        int priority);

  private:
    std::map<ORG_MOUSE_INPUT, MouseEvent> _mouseEventMap{};
    std::map<EntityReference, MouseEvent> _leftClickEventMap{};
    std::map<EntityReference, MouseEvent> _rightClickEventMap{};
    std::map<int, KeyEvent> _keyDownEventMap{};
    std::map<int, KeyEvent> _keyUpEventMap{};
    std::map<int, KeyEvent> _keyHoldEventMap{};

    // CHANGE THIS TO SHARED_PTR IF CONTROLLER EVER NEEDS TO BE THREAD SAFE.
    std::unique_ptr<uint8_t[]> _previousKeyState;

    bool _leftMouseDownTracker = false;
    bool _rightMouseDownTracker = false;
};
