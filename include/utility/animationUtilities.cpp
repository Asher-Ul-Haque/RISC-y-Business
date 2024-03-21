#include "animationUtilities.h"

AnimationUtilities::AnimationUtilities()
{
}

void AnimationUtilities::slide(sf::Transformable& TARGET, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION) 
{   
    aClock.restart();
    float elapsedTime = 0.0f;
    float totalDuration = DURATION;
    
    while (elapsedTime < totalDuration)
    {
        elapsedTime = aClock.getElapsedTime().asSeconds();
        float progress = std::min(1.0f, elapsedTime / totalDuration);
        sf::Vector2f interpolatedPosition = START + (END - START) * progress;
        TARGET.setPosition(interpolatedPosition);
    }
}

void AnimationUtilities::scale(sf::Transformable& TARGET, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION) 
{
    aClock.restart();
    float elapsedTime = 0.0f;
    float totalDuration = DURATION;
    
    while (elapsedTime < totalDuration)
    {
        elapsedTime = aClock.getElapsedTime().asSeconds();
        float progress = std::min(1.0f, elapsedTime / totalDuration);
        sf::Vector2f interpolatedScale = START + (END - START) * progress;
        TARGET.setScale(interpolatedScale);
    }
}


