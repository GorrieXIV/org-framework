#include "Timer.hpp"

Timer::Timer() : _startTicks(0),
                 _pausedTicks(0),
                 _paused(false),
                 _started(false)
{
}

void Timer::systemWait(const uint32_t time)
{
    SDL_Delay(time);
}

void Timer::start()
{
    _started = true;
    _paused = false;
    _startTicks = SDL_GetTicks();
    _pausedTicks = 0;
}

void Timer::stop()
{
    _started = false;
    _paused = false;
    _startTicks = 0;
    _pausedTicks = 0;
}

void Timer::pause()
{
    if (_started && !_paused) {
        _paused = true;

        _pausedTicks = SDL_GetTicks() - _startTicks;
        _startTicks = 0;
    }
}

void Timer::unpause()
{
    if (_started && _paused) {
        _paused = false;
        _startTicks = SDL_GetTicks() - _pausedTicks;
        _pausedTicks = 0;
    }
}

void Timer::syncFrame()
{
    int elapsedTime = getTicks();
    if (elapsedTime < FRAME_PERIOD) {
        systemWait(FRAME_PERIOD - elapsedTime);
    }
}

uint32 Timer::getTicks()
{
    uint32 time = 0;

    if (_started) {
        if (_paused) {
            // Return the number of ticks when the timer was paused.
            time = _pausedTicks;
        } else {
            // Return the current time minus the start time.
            time = SDL_GetTicks() - _startTicks;
        }
    }

    return time;
}

bool Timer::isStarted()
{
    // Timer is running and paused or unpaused.
    return _started;
}

bool Timer::isPaused()
{
    // Timer is paused.
    return _paused;
}
