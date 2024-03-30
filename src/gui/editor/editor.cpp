#include "editor.h"
#include <iostream>

IDE::IDE()
{
    window.create(sf::VideoMode(screenWidth, screenHeight), "RISC-Y Business", sf::Style::Close);
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - window.getSize().x / 2, sf::VideoMode::getDesktopMode().height / 2 - window.getSize().y / 2));
    window.setFramerateLimit(60);

    if (!font.loadFromFile(fontDirectoryPath + "JetBrainsMono-ExtraBold.ttf"))
    {
        std::cout << "Error loading JetBrainsMono-ExtraBold.ttf" << std::endl;
    }

    title.setFont(font);
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Black);
    title.setString(titleText);

    for (int i = 0; i < 4; i++)
    {
        if (!buttonTextures[i].loadFromFile(textureDirectoryPath + buttonTexturePaths[i]))
        {
            std::cout << "Error loading " << buttonTexturePaths[i] << std::endl;
        }
        buttons[i].setTexture(buttonTextures[i]);
        buttons[i].setPosition(50 + i * 200, 50);
    }

    topBar.setSize(sf::Vector2f(screenWidth, 50));
    topBar.setFillColor(sf::Color(30, 41, 59, 255));
    topBar.setPosition(0, 0);

    lineNumbers.setSize(sf::Vector2f(50, screenHeight));
    lineNumbers.setFillColor(backgroundColor);
    lineNumbers.setPosition(0, 50);
    lineNumbers.setOutlineColor(sf::Color(135, 136, 140));
    lineNumbers.setOutlineThickness(2);
}

void IDE::render()
{
    window.clear(backgroundColor);
    window.draw(lineNumbers);
    window.draw(topBar);
    window.draw(title);
    for (int i = 0; i < 4; i++)
    {
        window.draw(buttons[i]);
    }
    window.display();
}

void IDE::update()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void IDE::run()
{
    while (window.isOpen())
    {
        update();
        render();
    }
}

int main()
{
    IDE ide;
    ide.run();
    return 0;
}

//to compile : g++ editor.cpp -o editor -lsfml-graphics -lsfml-window -lsfml-system
