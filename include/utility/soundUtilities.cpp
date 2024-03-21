#include "soundUtilities.h"
#include <iostream>

SoundUtilities::SoundUtilities(std::string soundFilePath, float volume)
{
    if (!sSoundBuffer.loadFromFile(soundFilePath))
    {
        std::cout << "Error loading " << soundFilePath << std::endl;
    }
    sSoundEffect.setBuffer(sSoundBuffer);
    sSoundEffect.setVolume(volume);
}

void SoundUtilities::playSoundEffect()
{
    sSoundEffect.play();
}

void SoundUtilities::setVolume(float volume)
{
    sSoundEffect.setVolume(volume);
}

void SoundUtilities::pauseSoundEffect()
{
    sSoundEffect.pause();
}

void SoundUtilities::stopSoundEffect()
{
    sSoundEffect.stop();
}

void SoundUtilities::setPath(std::string soundFilePath)
{
    if (!sSoundBuffer.loadFromFile(soundFilePath))
    {
        std::cout << "Error loading " << soundFilePath << std::endl;
    }
    sSoundEffect.setBuffer(sSoundBuffer);
}

void SoundUtilities::playSoundEffectUntilFinished()
{
    sSoundEffect.play();
    while (sSoundEffect.getStatus() == sf::Sound::Playing)
    {
    }
}


