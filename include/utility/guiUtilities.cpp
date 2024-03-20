#include "guiUtilities.h"
#include <iostream>

guiUtilities::guiUtilities()
{
}

bool guiUtilities::isPointInRectangle(sf::Vector2f POINT, sf::Vector2f CENTER, sf::Vector2f SIZE)
{
    return (POINT.x >= CENTER.x - SIZE.x / 2 && POINT.x <= CENTER.x + SIZE.x / 2 && POINT.y >= CENTER.y - SIZE.y / 2 && POINT.y <= CENTER.y + SIZE.y / 2);
}

bool guiUtilities::isPointInCircle(sf::Vector2f POINT, sf::Vector2f CENTER, float RADIUS)
{
    return (POINT.x - CENTER.x) * (POINT.x - CENTER.x) + (POINT.y - CENTER.y) * (POINT.y - CENTER.y) <= RADIUS * RADIUS;
}

bool guiUtilities::isMousePressedInRectangle(sf::Vector2f CENTER, sf::Vector2f SIZE, sf::RenderWindow* WINDOW)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*WINDOW);
    return (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isPointInRectangle(sf::Vector2f(mousePosition), CENTER, SIZE));
}

bool guiUtilities::isMousePressedInCircle(sf::Vector2f CENTER, float RADIUS, sf::RenderWindow* WINDOW)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*WINDOW);
    return (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isPointInCircle(sf::Vector2f(mousePosition), CENTER, RADIUS));
}

bool guiUtilities::isMouseInRectangle(sf::Vector2f CENTER, sf::Vector2f SIZE, sf::RenderWindow* WINDOW)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*WINDOW);
    return isPointInRectangle(sf::Vector2f(mousePosition), CENTER, SIZE);
}

bool guiUtilities::isMouseInCircle(sf::Vector2f CENTER, float RADIUS, sf::RenderWindow* WINDOW)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*WINDOW);
    return isPointInCircle(sf::Vector2f(mousePosition), CENTER, RADIUS);
}

