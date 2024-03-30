#include "editor.h"
#include <iostream>

IDE::IDE() 
    : soundEffects(soundDirectoryPath + "click.wav", 50),
    animation([this](){render();})
{
    window.create(sf::VideoMode(screenWidth, screenHeight), "RISC-Y Business", sf::Style::Close);
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - window.getSize().x / 2, sf::VideoMode::getDesktopMode().height / 2 - window.getSize().y / 2));
    window.setFramerateLimit(60);

    if (!font.loadFromFile(fontDirectoryPath + "JetBrainsMono-Light.ttf"))
    {
        std::cout << "Error loading JetBrainsMono-ExtraBold.ttf" << std::endl;
    }

    title.setFont(font);
    title.setCharacterSize(16);
    title.setFillColor(sf::Color::White);
    title.setString(titleText);
    title.setPosition(30, 15);

    for (int i = 0; i < 4; i++)
    {
        if (!buttonTextures[i].loadFromFile(textureDirectoryPath + buttonTexturePaths[i]))
        {
            std::cout << "Error loading " << buttonTexturePaths[i] << std::endl;
        }
        buttons[i].setTexture(buttonTextures[i]);
        buttons[i].setOrigin(buttonTextures[i].getSize().x / 2, buttonTextures[i].getSize().y / 2);
        buttons[i].setPosition(screenWidth - 50 * (i + 1), 0);
    }
    
    topBarTexture.loadFromFile(textureDirectoryPath + topBarTexturePath);
    topBar.setTexture(&topBarTexture);
    topBar.setSize(sf::Vector2f(screenWidth, 50));
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
        switch (event.type)
        {
            default:
                break;

            case sf::Event::Closed:
                soundEffects.setPath(soundDirectoryPath + "failure.wav");
                soundEffects.playSoundEffect();
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                switch(event.mouseButton.button)
                {
                    case sf::Mouse::Left:
                        for (int i = 0; i < 4; ++i)
                        {
                            switch (MouseUtilities::isMouseInRectangle(buttons[i].getPosition(), sf::Vector2f(buttonTextures[i].getSize().x, buttonTextures[i].getSize().y), &window))
                            {
                                case true:
                                    soundEffects.playSoundEffect();
                                    std::cout << "Button " << i << " clicked" << std::endl;
                                    break;

                                case false:
                                    break;
                            }
                        }

                        default:
                            break;
                }

            case sf::Event::MouseMoved:
                for (int i = 0; i < 4; ++i)
                {
                    switch (MouseUtilities::isMouseInRectangle(buttons[i].getPosition(), sf::Vector2f(buttonTextures[i].getSize().x, buttonTextures[i].getSize().y), &window))
                    {
                        case true:
                            switch(isAnimating[i])
                            {
                                case false:
                                    
                                    animation.scale(buttons[i], sf::Vector2f(1, 1), sf::Vector2f(1.1, 1.1), 0.1);
                                isAnimating[i] = true;
                                break;

                                case true:
                                    break;
                            }

                        case false:
                            switch(isAnimating[i])
                            {
                                case true:
                                    animation.scale(buttons[i], sf::Vector2f(1.1, 1.1), sf::Vector2f(1, 1), 0.1);
                                    isAnimating[i] = false;
                                    break;

                                case false:
                                    break;
                            }
                    }
                }
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

