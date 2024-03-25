#include "menuUtilities.h"
#include "soundUtilities.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
// - - - - - - - - -

TextBox::TextBox(sf::RenderWindow* WINDOW, sf::Vector2f POSITION, sf::Vector2f SIZE) : window(WINDOW), position(POSITION), size(SIZE), soundEffects(soundDirectoryPath + keypressSoundFilePath, 50)
{
    textBox.setSize(size);
    textBox.setPosition(position);
    textBox.setFillColor(sf::Color(239, 239, 239, 255));
    textBox.setOutlineThickness(2);
    textBox.setOutlineColor(sf::Color::Black);

    font.loadFromFile(fontDirectoryPath + "JetBrainsMono-ExtraBold.ttf");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(position.x + 5, position.y + 5);
    text.setFont(font);

    cursor.setSize(sf::Vector2f(2, 20));
    cursor.setFillColor(sf::Color::Black);
    cursor.setPosition(text.getPosition().x + text.getGlobalBounds().width + 5, text.getPosition().y);

    testRect.setSize(size);
    testRect.setFillColor(sf::Color(239, 239, 239, 255));
    testRect.setOutlineThickness(2);
    testRect.setOutlineColor(sf::Color::Black);
    testRect.setPosition(position);
}

// - - - - - - - - -

void TextBox::handleInput(sf::Event* EVENT)
{
    std::string input = "";
    switch(EVENT->type)
    {
        case sf::Event::TextEntered:
            switch(EVENT->text.unicode >= 32 && EVENT->text.unicode <=126)
            {
                case true:
                    input += (char) EVENT->text.unicode;
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
        case sf::Event::KeyPressed:
            switch(EVENT->key.code)
            {
                case sf::Keyboard::BackSpace:
                    if(input.size() > 0)
                    {
                        input.pop_back();
                        text.setString(input);
                        updateCursorPosition();
                    }
                    break;

                case sf::Keyboard::Return:
                    break;

                default:
                    input += (char) EVENT->text.unicode;
            }
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
    text.setString("test");
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
