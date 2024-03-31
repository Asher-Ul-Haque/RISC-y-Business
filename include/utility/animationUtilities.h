#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include <functional>
// - - - - - - - - -

class AnimationUtilities 
{
sf::Clock aClock;
std::function<void()> renderFunction;
// - - - - - - - - -
public:
    AnimationUtilities(std::function<void()> renderFunction);
    void slide(sf::Transformable& TARGET, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION);
    void scale(sf::Transformable& TARGET, const sf::Vector2f& START, const sf::Vector2f& END, float DURATION);
};

// - - - - - - - - -
#endif // ANIMATION_H
