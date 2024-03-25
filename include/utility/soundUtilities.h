#ifndef SOUNDUTILITIES_H
#define SOUNDUTILITIES_H
#include <SFML/Audio.hpp>
// - - - - - - - - -

class SoundUtilities
{

sf::Sound sSoundEffect;
sf::SoundBuffer sSoundBuffer;

public:
    SoundUtilities(std::string soundFilePath, float volume);
    void setVolume(float volume);
    void setPath(std::string soundFilePath);
    // - - - - - - - - -
    void playSoundEffect();
    void playSoundEffectUntilFinished();
    void pauseSoundEffect();
    void stopSoundEffect();
    // - - - - - - - - -

};

// - - - - - - - - -
#endif // SOUNDUTILITIES_H
