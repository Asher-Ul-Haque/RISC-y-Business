#include "menuUtilities.h"
#include "soundUtilities.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <filesystem>
// - - - - - - - - -

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

// - - - - - - - - -

TextBox::TextBox(sf::RenderWindow* WINDOW, sf::Vector2f POSITION) : window(WINDOW), position(POSITION), soundEffects(soundDirectoryPath + keypressSoundFilePath, 50)
{
    textBoxTexture.loadFromFile(textureDirectoryPath + emptyBarTextureFilePath);  
    textBox.setTexture(textBoxTexture);
    textBox.setPosition(position);
    textBox.setOrigin(textBoxTexture.getSize().x / 2, textBoxTexture.getSize().y / 2);
    
    font.loadFromFile(fontDirectoryPath + "JetBrainsMono-Light.ttf");
    text.setCharacterSize(15);
    text.setFillColor(sf::Color(150, 150, 150));
    text.setPosition(textBox.getPosition().x + 5 - 400/2, textBox.getPosition().y - 5);
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
    if (input == "")
    {
        text.setString("Enter project name");
        text.setFillColor(sf::Color(150, 150, 150));
        cursor.setPosition(text.getPosition().x + text.getGlobalBounds().width + 5, cursor.getPosition().y);
    }
    if (input == "Enter valid project name")
    {
        text.setFillColor(sf::Color::Red);
    }
    else
    {
        text.setFillColor(sf::Color::Black);
    }
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
}

// - - - - - - - - -

std::string TextBox::getInput()
{
    return input;
}

// - - - - - - - - -

void TextBox::error()
{
    soundEffects.setPath(soundDirectoryPath + "failure.wav");
    soundEffects.playSoundEffect();
    sf::Clock clock;
    input = "Enter valid project name";
    text.setFillColor(sf::Color::Red);
    text.setString(input);
    updateCursorPosition();
    edited = false;
}

// - - - - - - - - -

DropDown::DropDown(sf::RenderWindow* WINDOW, sf::Vector2f POSITION): window(WINDOW), isOpen(false), soundEffects(soundDirectoryPath + toggleSoundFilePath, 50)
{
    for (const auto& entry : std::filesystem::directory_iterator(projectsDirectoryPath))
    {
        options.push_back(entry.path().filename().string());
    }
    
    textBoxTexture.loadFromFile(textureDirectoryPath + emptyDropDownTextureFilePath);
    textBox.setTexture(textBoxTexture);
    textBox.setOrigin(textBoxTexture.getSize().x / 2, textBoxTexture.getSize().y / 2);
    textBox.setPosition(POSITION.x, POSITION.y);
    
    menuTexture.loadFromFile(textureDirectoryPath + emptyMenuTextureFilePath); 
    menu.setTexture(menuTexture);
    menu.setOrigin(menuTexture.getSize().x / 2, menuTexture.getSize().y / 2);
    menu.setPosition(textBox.getPosition().x, textBox.getPosition().y + textBoxTexture.getSize().y / 2 + 45);

    highlightTexture.loadFromFile(textureDirectoryPath + highlightTextureFilePath);
    highlight.setTexture(highlightTexture);
    highlight.setOrigin(highlightTexture.getSize().x / 2, highlightTexture.getSize().y / 2);

    font.loadFromFile(fontDirectoryPath + "JetBrainsMono-Light.ttf");
    selectedText.setFont(font);
    selectedText.setCharacterSize(15);
    selectedText.setFillColor(sf::Color::Black);
    selectedText.setString("Select project");
    selectedText.setOrigin(selectedText.getGlobalBounds().width / 2, selectedText.getGlobalBounds().height / 2);
    selectedText.setPosition(textBox.getPosition().x, textBox.getPosition().y - 3);

    for (int i = 0; i < options.size(); i++)
    {
        sf::Text option;
        option.setFont(font);
        option.setCharacterSize(15);
        option.setFillColor(sf::Color::Black);
        option.setString(options[i]);
        option.setOrigin(option.getGlobalBounds().width / 2, option.getGlobalBounds().height / 2);
        option.setPosition(textBox.getPosition().x, textBox.getPosition().y + 25 * (i + 1));
        optionTexts.push_back(option);
        if (i == 0)
        {
            selectedText.setString(option.getString());
            selectedText.setOrigin(selectedText.getGlobalBounds().width / 2, selectedText.getGlobalBounds().height / 2);
        }
    }
}

// - - - - - - - - -

void DropDown::toggleDropdown()
{
    soundEffects.playSoundEffect();
    isOpen = !isOpen;
    if (isOpen) //Refresh all the options from the folder
    {
        options.clear();
        for (const auto& entry : std::filesystem::directory_iterator(projectsDirectoryPath))
        {
            options.push_back(entry.path().filename().string());
        }
        optionTexts.clear();
        for (int i = 0; i < options.size(); i++)
        {
            sf::Text option;
            option.setFont(font);
            option.setCharacterSize(15);
            option.setFillColor(sf::Color::Black);
            option.setString(options[i]);
            option.setOrigin(option.getGlobalBounds().width / 2, option.getGlobalBounds().height / 2);
            option.setPosition(textBox.getPosition().x, textBox.getPosition().y + 25 * (i + 1));
            optionTexts.push_back(option);
            if (i == 0)
            {
                selectedText.setString(option.getString());
                selectedText.setOrigin(selectedText.getGlobalBounds().width / 2, selectedText.getGlobalBounds().height / 2);
            }
        }
    }
}

// - - - - - - - - -

void DropDown::handleInput(const sf::Event* event)
{
    switch(event->type)
    {
        case sf::Event::KeyPressed:
            switch(event->key.code)
            {
                case sf::Keyboard::O:
                    toggleDropdown();
                    break;

                case sf::Keyboard::Down:
                    if (!isOpen)
                    {
                        return;
                    }
                    if (selectedIndex < optionTexts.size() - 1)
                    {
                        selectedIndex++;
                        selectedText.setString(optionTexts[selectedIndex].getString());
                        selectedText.setOrigin(selectedText.getGlobalBounds().width / 2, selectedText.getGlobalBounds().height / 2);
                    } 
                    break;

                case sf::Keyboard::Up:
                    if (!isOpen)
                    {
                        return;
                    }
                    if (selectedIndex > 0)
                    {
                        selectedIndex--;
                        selectedText.setString(optionTexts[selectedIndex].getString());
                        selectedText.setOrigin(selectedText.getGlobalBounds().width / 2, selectedText.getGlobalBounds().height / 2);
                    }
                    break;

                default:
                    break;
            }

        default:
            break;
    }

    switch(MouseUtilities::isMousePressedInRectangle(textBox.getPosition(), sf::Vector2f(450, 60), event))
    {
        case true:
            toggleDropdown();
            break;

        case false:
            break;
    }

    switch(MouseUtilities::isMousePressedInRectangle(menu.getPosition(), sf::Vector2f(450, 60), event))
    {
        case true:
            if (!isOpen)
            {
                return;
            }
            for (int i = 0; i < optionTexts.size(); i++)
            {
                switch(MouseUtilities::isMousePressedInRectangle(optionTexts[i].getPosition(), sf::Vector2f(optionTexts[i].getGlobalBounds().width, optionTexts[i].getGlobalBounds().height), event))
                {
                    case true:
                        selectedText.setString(optionTexts[i].getString());
                        selectedText.setOrigin(selectedText.getGlobalBounds().width / 2, selectedText.getGlobalBounds().height / 2);
                        toggleDropdown();
                        break;

                    case false:
                        break;
                }
            }
            break;

        case false:
            break;
    }
}

// - - - - - - - - -

void DropDown::render() 
{
    window->draw(textBox);
    window->draw(selectedText);
    if (isOpen) 
    {
        window->draw(menu);

        int startIndex = max(0, selectedIndex - 1); 
        int endIndex = min(options.size() - 1, startIndex + 2);
        
        if (endIndex >= startIndex)
        {
            highlight.setPosition(optionTexts[selectedIndex].getPosition().x, optionTexts[selectedIndex].getPosition().y + 3);
            window->draw(highlight);
        }

        for (int i = startIndex; i <= endIndex; i++) 
        {
            optionTexts[i].setPosition(menu.getPosition().x, menu.getPosition().y - menuTexture.getSize().y/2 + 35 + (i - startIndex) * 20);
            window->draw(optionTexts[i]);
        }
    }
}

// - - - - - - - - -

void DropDown::error()
{
    soundEffects.setPath(soundDirectoryPath + "failure.wav");
    soundEffects.playSoundEffect();
}

// - - - - - - - - -

void DropDown::setOptions(const std::vector<std::string>& OPTIONS)
{
    options = OPTIONS;
}

// - - - - - - - - -

std::string DropDown::getSelectedOption() const
{
    return selectedText.getString();
}

// - - - - - - - - -


