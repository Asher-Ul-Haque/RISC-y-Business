#include "loadingScreen.h"
#include <iostream>

LoadingScreen::LoadingScreen()
{
    window.create(sf::VideoMode(650, 400), "RISC-Y Business", sf::Style::Close);
    window.setFramerateLimit(60);
    window.clear(backgroundColor);
    window.display();

    if (!logoTexture.loadFromFile(textureDirectoryPath + "logo.png"))
    {
        std::cout << "Error loading logo.png" << std::endl;
    }
    logoTexture.setSmooth(true);
    window.setIcon(521, 479, logoTexture.copyToImage().getPixelsPtr());

    logoSprite.setTexture(logoTexture);
    logoSprite.setScale(logoSize.x / logoTexture.getSize().x, logoSize.y / logoTexture.getSize().y);
    logoSprite.setPosition(logoPosition.x, logoPosition.y);

    if (!font.loadFromFile(fontDirectoryPath + "JetBrainsMono-ExtraBold.ttf"))
    {
        std::cout << "Error loading JetBrainsMono-ExtraBold.ttf" << std::endl;
    }
    title.setFont(font);
    title.setString("Loading...");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Black);
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition(logoPosition.x + 102, logoPosition.y + logoSize.y + 50);
}

void LoadingScreen::run()
{
    while (window.isOpen())
    {
        update();
        render();
    }
}

void LoadingScreen::update()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                break;

            default:
                break;
        }
    }
}

void LoadingScreen::render()
{
    window.clear(backgroundColor);
    window.draw(logoSprite);
    window.draw(title);
    window.display();
}


