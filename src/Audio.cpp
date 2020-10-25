#include "Audio.hpp"

SoundBoard::SoundBoard()
{
}

SoundBoard::~SoundBoard()
{
    Mix_FreeMusic(_testTrack);
    _testTrack = NULL;

    Mix_Quit();
}

void SoundBoard::loadTrackFromFile(const std::string& trackIdentifier,
                                   const std::string& audioFilename)
{
    _testTrack = Mix_LoadMUS(audioFilename.c_str());
    if (_testTrack == NULL) {
        std::cout << "error loading audio track: " << Mix_GetError() << std::endl;
    }
} // loadTrackFromFile

void SoundBoard::toggleBgMusic()
{
    // If no music is playing, load the bg track.
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(_testTrack, -1);
    } else {
        // If the bg track is loaded but paused, resume.
        // Otherwise the track is loaded and playing, so pause.
        if (Mix_PausedMusic() == 1) {
            Mix_ResumeMusic();
        } else {
            Mix_PauseMusic();
        }
    }
}
