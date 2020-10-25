#pragma once

#include "SDL.h"
#include "Window.hpp"

class SoundBoard {
  public:
    /// Default Constructor.
    SoundBoard();

    /// Destructor.
    ~SoundBoard();

    /// Close the SoundBoard and free any occupied memory.
    void close();

    /// Load audio track by filename.
    void loadTrackFromFile(const std::string& trackIdentifier,
                           const std::string& audioFilename);

    /// Temporary API call to toggle the audio track currently referenced by `_testTrack`.
    void toggleBgMusic();

  private:
    Mix_Music* _testTrack = NULL;
    std::map<std::string, Mix_Music*> _audioTracks{};
};
