#include "menuUtilities.h"
#include "soundUtilities.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
// - - - - - - - - -

TextBox::TextBox(sf::RenderWindow* WINDOW, sf::Vector2f POSITION, sf::Vector2f SIZE) : window(WINDOW), position(POSITION), size(SIZE), soundEffects(soundDirectoryPath + keypressSoundFilePath, 50)
{
    textBox.setSize(size);
    textBox.setPosition(position);
    textBox.setFillColor(sf::Color::White);
    textBox.setOutlineThickness(2);
    textBox.setOutlineColor(sf::Color(201, 205, 215));
    textBox.setOrigin(textBox.getSize().x/2, textBox.getSize().y/2);

    font.loadFromFile(fontDirectoryPath + "JetBrainsMono-ExtraBold.ttf");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(position.x + 5 - size.x/2, position.y - 15);
    text.setOrigin(0, text.getGlobalBounds().height / 2);
    text.setFont(font);

    cursor.setSize(sf::Vector2f(2, 20));
    cursor.setFillColor(sf::Color::Black);
    cursor.setOrigin(1, cursor.getSize().y / 2);
    cursor.setPosition(text.getPosition().x + text.getGlobalBounds().width + 5, text.getPosition().y + 10);
}

// - - - - - - - - -

void TextBox::handleInput(sf::Event* EVENT)
{
    switch(EVENT->type)
    {
        case sf::Event::TextEntered:
            switch(EVENT->text.unicode >= 32 && EVENT->text.unicode <= 126 && text.getGlobalBounds().width < textBox.getSize().x - 20)
            {
                case true:
                    input += static_cast<char>(EVENT->text.unicode);
                    text.setString(input);
                    updateCursorPosition();
                    break;

                case false:
                    switch(EVENT->text.unicode == 8 && input.size() > 0)
                    {
                        case true:
                            input.pop_back();
                            text.setString(input);
                            updateCursorPosition();
                            break;

                        case false:
                            break;
                    }
                    break;
            }
            break;

        default:
            break;
    }
}

// - - - - - - - - -

void TextBox::updateCursorPosition()
{
    sf::FloatRect textBounds = text.getLocalBounds();
    cursor.setPosition(text.getPosition().x + textBounds.width + 5, cursor.getPosition().y);
}

// - - - - - - - - -

void TextBox::render()
{
    window->draw(textBox);
    window->draw(text);
    if(showCursor)
    {
        window->draw(cursor);
    }
}

// - - - - - - - - -
/*
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
    TextBox textBox(&window, sf::Vector2f(50, 50), sf::Vector2f(200, 50));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            textBox.handleInput(event);
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        textBox.render();
        window.display();
    }
    return 0;
}
*/
