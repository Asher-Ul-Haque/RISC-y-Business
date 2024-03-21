#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>

class AnimationUtilities 
{

public:
    AnimationUtilities();

    void slide(sf::Transformable& TARGET, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION);
    void scale(sf::Transformable& TARGET, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION);

private:
    sf::Clock aClock;
};

#endif // ANIMATION_H
