#include <iostream>
#include <SFML/Graphics.hpp>
#include "menuUtilities.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
    TextBox textBox(&window, sf::Vector2f(50, 50), sf::Vector2f(200, 50));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            textBox.handleInput(&event);
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        textBox.render();
        window.display();
    }
    return 0;
}
