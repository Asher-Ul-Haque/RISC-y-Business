#include "menuUtilities.h"
#include "soundUtilities.h"
#include <SFML/Graphics/Rect.hpp>

TextBox::TextBox(sf::RenderWindow& WINDOW, sf::Vector2f POSITION, sf::Vector2f SIZE) : window(WINDOW), position(POSITION), size(SIZE), soundEffects(soundDirectoryPath + keypressSoundFilePath, 50)
{
    textBox.setSize(size);
    textBox.setPosition(position);
    textBox.setFillColor(sf::Color(239, 239, 239, 255));
    textBox.setOutlineThickness(2);
    textBox.setOutlineColor(sf::Color::Black);

    sf::Font font;
    font.loadFromFile(fontDirectoryPath + "JetBrainsMono-ExtraBold.ttf");
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(position.x + 5, position.y + 5);

    cursor.setSize(sf::Vector2f(2, 20));
    cursor.setFillColor(sf::Color::Black);
    cursor.setPosition(text.getPosition().x + text.getGlobalBounds().width + 5, text.getPosition().y);
}

void TextBox::handleInput(sf::Event& EVENT)
{
    std::string input = "";
    switch(EVENT.type)
    {
        case sf::Event::TextEntered:
            switch(EVENT.text.unicode >= 32 && EVENT.text.unicode <=126)
            {
                case true:
                    input += (char) EVENT.text.unicode;
                    break;

                case false:
                    switch(EVENT.text.unicode == 8 && input.size() > 0)
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
    }
}

void TextBox::updateCursorPosition()
{
    sf::FloatRect textBounds = text.getLocalBounds();
    cursor.setPosition(text.getPosition().x + textBounds.width + 5, cursor.getPosition().y);
}

void TextBox::render()
{
    window.draw(textBox);
    window.draw(text);
    if (showCursor)
    {
        window.draw(cursor);
    }
}
