#include "startScreen.h"
#include <iostream>

StartScreen::StartScreen()
{
    window.create(sf::VideoMode(1000, 750), "Welcome to RISC-Y Business");
    window.setFramerateLimit(60);

    if (!logoTexture.loadFromFile(textureDirectoryPath + "logo.png"))
    {
        std::cout << "Error loading logo.png" << std::endl;
    }
    logoTexture.setSmooth(true);
    logoSprite.setTexture(logoTexture);
    logoSprite.setScale(logoSize.x / logoTexture.getSize().x, logoSize.y / logoTexture.getSize().y);
    logoSprite.setPosition(logoPosition.x, logoPosition.y);

    if (!openTexture.loadFromFile(textureDirectoryPath + "open.png"))
    {
        std::cout << "Error loading open.png" << std::endl;
    }
    openTexture.setSmooth(true);
    openSprite.setOrigin(buttonSize.x / 2, buttonSize.y / 2);
    openSprite.setTexture(openTexture);
    openSprite.setPosition(openButtonPosition.x, openButtonPosition.y);

    if (!newTexture.loadFromFile(textureDirectoryPath + "new.png"))
    {
        std::cout << "Error loading new.png" << std::endl;
    }
    newTexture.setSmooth(true);
    newSprite.setTexture(newTexture);
    newSprite.setOrigin(buttonSize.x / 2, buttonSize.y / 2);
    newSprite.setPosition(newButtonPosition.x, newButtonPosition.y);

    if (!font.loadFromFile(fontDirectoryPath + "JetBrainsMono-ExtraBold.ttf"))
    {
        std::cout << "Error loading JetBrainsMono-ExtraBold.ttf" << std::endl;
    }
    title.setFont(font);
    title.setString("RISC-Y Business");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::Black);
    title.setPosition(logoPosition.x, logoPosition.y + logoSize.y + 20);
}

void StartScreen::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void StartScreen::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::O:
                        std::cout << "Open file" << std::endl;
                        break;
                    case sf::Keyboard::N:
                        std::cout << "New file" << std::endl;
                        break;
                    default:
                        break;
                }
                break;

            case sf::Event::MouseMoved:
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (isMouseOverButton(openButtonPosition, buttonSize, mousePos))
                {
                    isMouseOverOpenButton = true;
                    //While mouse is over open button, increase the size of the open button
                    while (openSprite.getScale().x < 1.1)
                    {
                        openSprite.setScale(openSprite.getScale().x + 0.0001, openSprite.getScale().y + 0.0001);
                    }
                }
                else
                {
                    isMouseOverOpenButton = false;
                    while (openSprite.getScale().x > 1)
                    {
                        openSprite.setScale(openSprite.getScale().x - 0.0001, openSprite.getScale().y - 0.0001);
                    }
                }
                if (isMouseOverButton(newButtonPosition, buttonSize, mousePos))
                {
                    isMouseOverNewButton = true;
                    //While mouse is over new button, increase the size of the new button
                    while (newSprite.getScale().x < 1.1)
                    {
                        newSprite.setScale(newSprite.getScale().x + 0.0001, newSprite.getScale().y + 0.0001);
                    }
                }
                else
                {
                    isMouseOverNewButton = false;
                    while (newSprite.getScale().x > 1)
                    {
                        newSprite.setScale(newSprite.getScale().x - 0.0001, newSprite.getScale().y - 0.0001);
                    }
                }
                break;
        }
    }
}

void StartScreen::update()
{
}

void StartScreen::render()
{
    window.clear(sf::Color(239, 239, 239, 255));
    window.draw(logoSprite);
    window.draw(title);
    window.draw(newSprite);
    window.draw(openSprite);
    window.display();
}


int main() 
{
    StartScreen startScreen;
    startScreen.run();
    return 0;
}

bool StartScreen::isMouseOverButton(sf::Vector2f buttonPosition, sf::Vector2f buttonSize, sf::Vector2i mousePosition)
{
    if (mousePosition.x > buttonPosition.x - buttonSize.x/2 && mousePosition.x < buttonPosition.x + buttonSize.x/2)
    {
        if (mousePosition.y > buttonPosition.y - buttonSize.y/2 && mousePosition.y < buttonPosition.y + buttonSize.y / 2)
        {
            return true;
        }
    }
    return false;
}


