#ifndef MENUUTILITIES_H
#define MENUUTILITIES_H
#include <SFML/Graphics.hpp>
#include "soundUtilities.h"
#include <iostream>

class TextBox
{
public:
    TextBox(sf::RenderWindow& WINDOW, sf::Vector2f POSITION, sf::Vector2f SIZE);
    void handleInput(sf::Event& EVENT);
    void render();

private:
    sf::RenderWindow& window;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::RectangleShape textBox;
    sf::Text text;
    sf::Font font;
    SoundUtilities soundEffects;
    bool showCursor = false;
    std::string textString = "";
    std::string fontDirectoryPath = "../resources/fonts/";
    std::string soundDirectoryPath = "../resources/sounds/";
    std::string keypressSoundFilePath = "keypress.wav";
    std::string backspaceSoundFilePath = "backspace.wav";
    sf::RectangleShape cursor;

    void updateCursorPosition();
};

#endif//MENUUTILITIES_H

