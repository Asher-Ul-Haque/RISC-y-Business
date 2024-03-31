#ifndef MENUUTILITIES_H
#define MENUUTILITIES_H
#include <SFML/Graphics.hpp>
#include "soundUtilities.h"
#include "mouseUtilities.h"
// - - - - - - - - -

class TextBox
{
std::string fontDirectoryPath = "../../include/resources/fonts/";
std::string soundDirectoryPath = "../../include/resources/sounds/";
std::string textureDirectoryPath = "../../include/resources/textures/";
// - - - - - - - - -
std::string emptyBarTextureFilePath = "bar.png";
std::string keypressSoundFilePath = "keypress.wav";
std::string backspaceSoundFilePath = "backspace.wav";

SoundUtilities soundEffects;
sf::Clock cursorClock;

sf::Sprite textBox;
sf::Texture textBoxTexture;
sf::RectangleShape cursor;
sf::Text text;
sf::Font font;
// - - - - - - - - -
bool showCursor = true;
void updateCursorPosition();
// - - - - - - - - -
std::string input = "Enter project name";
bool edited = false;

sf::RenderWindow* window;
sf::Vector2f position;

MouseUtilities mouseUtilities;


public:

TextBox(sf::RenderWindow* WINDOW, sf::Vector2f POSITION);
void handleInput(sf::Event* EVENT);
std::string getInput();
void error();
void render();
};

// - - - - - - - - -

class DropDown
{
std::string fontDirectoryPath = "../../include/resources/fonts/";
std::string soundDirectoryPath = "../../include/resources/sounds/";
std::string textureDirectoryPath = "../../include/resources/textures/";
std::string projectsDirectoryPath = std::getenv("HOME") + std::string("/RISCY Projects"); 
// - - - - - - - - -
std::string emptyDropDownTextureFilePath = "dropdown.png";
std::string emptyMenuTextureFilePath = "dropdownmenu.png";
std::string highlightTextureFilePath = "highlight.png";
std::string toggleSoundFilePath = "toggle.wav";
std::string backspaceSoundFilePath = "backspace.wav";
std::string scrollSoundFilePath = "scroll.wav";

SoundUtilities soundEffects;

unsigned char selectedIndex = 0;
sf::Texture textBoxTexture;
sf::Texture menuTexture;
sf::Texture highlightTexture;
sf::Sprite textBox;
sf::Sprite menu;
sf::Sprite highlight;
sf::Text selectedText;
std::vector<sf::Text> optionTexts;
std::vector<std::string> options;
sf::Font font;

sf::RenderWindow* window;
sf::Vector2f position;
bool isOpen;
// - - - - - - - - -
void toggleDropdown();

public:
    
DropDown(sf::RenderWindow* WINDOW, sf::Vector2f POSITION);
void handleInput(const sf::Event* event);
void render();
void error();
void setOptions(const std::vector<std::string>& OPTIONS);
std::string getSelectedOption() const;
};



// - - - - - - - - -
#endif//MENUUTILITIES_H

