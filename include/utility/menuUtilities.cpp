#include "menuUtilities.h"
#include "soundUtilities.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
// - - - - - - - - -

TextBox::TextBox(sf::RenderWindow* WINDOW, sf::Vector2f POSITION, sf::Vector2f SIZE) : window(WINDOW), position(POSITION), size(SIZE), soundEffects(soundDirectoryPath + keypressSoundFilePath, 50)
{
    textBoxTexture.loadFromFile(textureDirectoryPath + emptyBarTextureFilePath);  
    textBox.setTexture(textBoxTexture);
    textBox.setPosition(position);
    textBox.setOrigin(size.x / 2, size.y / 2);
    
    font.loadFromFile(fontDirectoryPath + "JetBrainsMono-Light.ttf");
    text.setCharacterSize(15);
    text.setFillColor(sf::Color(100, 100, 100));
    text.setPosition(textBox.getPosition().x + 5 - size.x/2, textBox.getPosition().y - 5);
    text.setOrigin(0, text.getGlobalBounds().height / 2);
    text.setFont(font);
    text.setString("Enter project name");

    cursor.setSize(sf::Vector2f(2, 20));
    cursor.setFillColor(sf::Color::Black);
    cursor.setOrigin(1, cursor.getSize().y / 2);
    cursor.setPosition(text.getPosition().x + text.getGlobalBounds().width + 5, textBox.getPosition().y);
}

// - - - - - - - - -

void TextBox::handleInput(sf::Event* EVENT)
{
    if (!edited)
    {
        input = "";
        edited = true;
    }
    text.setFillColor(sf::Color::Black);
    switch(EVENT->type)
    {
        case sf::Event::TextEntered:
            switch(EVENT->text.unicode >= 32 && EVENT->text.unicode <= 126 && text.getGlobalBounds().width < textBoxTexture.getSize().x - 20)
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
    if (cursorClock.getElapsedTime().asSeconds() > 0.5)
    {
        showCursor = !showCursor;
        cursorClock.restart();
    }
    if (showCursor)
    {
        window->draw(cursor);
    }
    if (input == "")
    {
        text.setString("Enter project name");
        text.setFillColor(sf::Color(20, 20, 20));
        cursor.setPosition(text.getPosition().x + text.getGlobalBounds().width + 5, cursor.getPosition().y);
    }
}

// - - - - - - - - -

std::string TextBox::getInput()
{
    return input;
}

// - - - - - - - - -

void TextBox::error()
{
    soundEffects.playSoundEffect();
    input = "Enter valid project name";
    text.setFillColor(sf::Color::Red);
    text.setString(input);
    updateCursorPosition();
    edited = false;
}
