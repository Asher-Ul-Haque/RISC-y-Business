#ifndef MENUUTILITIES_H
#define MENUUTILITIES_H
#include <SFML/Graphics.hpp>
#include "soundUtilities.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
// - - - - - - - - -

class TextBox
{

std::string fontDirectoryPath = "../../include/resources/fonts/";
std::string soundDirectoryPath = "../../include/resources/sounds/";
std::string textureDirectoryPath = "../../include/resources/textures/";
std::string emptyBarTextureFilePath = "bar.png";
std::string keypressSoundFilePath = "keypress.wav";
std::string backspaceSoundFilePath = "backspace.wav";
// - - - - - - - - -
SoundUtilities soundEffects;
// - - - - - - - - -
sf::Sprite textBox;
sf::Texture textBoxTexture;
sf::RectangleShape cursor;
sf::Text text;
sf::Font font;
bool showCursor = true;
void updateCursorPosition();
// - - - - - - - - -
sf::RenderWindow* window;
sf::Vector2f position;
sf::Vector2f size;
std::string input = "Enter project name";
// - - - - - - - - -
sf::Clock cursorClock;
bool edited = false;

public:
TextBox(sf::RenderWindow* WINDOW, sf::Vector2f POSITION, sf::Vector2f SIZE);
void handleInput(sf::Event* EVENT);
void render();
void error();
std::string getInput();
};

// - - - - - - - - -
#endif//MENUUTILITIES_H

