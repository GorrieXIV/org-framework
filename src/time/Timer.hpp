#pragma once

#include "platform.hpp"

typedef unsigned long int uint32;

class Timer {

  public:
    /// Constructor
    Timer();

    /// Wait for /time/ miliseconds.
    static void systemWait(const uint32_t time);

    void start();
    void stop();
    void pause();
    void unpause();

    /// Counts the number of ticks and pauses until FRAME_PERIOD to make up the difference.
    void syncFrame();

    uint32 getTicks();

    /// Checks the status of the timer
    bool isStarted();
    bool isPaused();

  private:
    // The clock time when the timer starts.
    uint32 _startTicks = 0;

    // The ticks stored when the timer was paused.
    uint32 _pausedTicks = 0;

    bool _paused  = false;
    bool _started = false;

};
