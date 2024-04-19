#include "startScreen.h"
#include <iostream>

StartScreen::StartScreen() : clickSound(soundDirectoryPath + clickSoundFilePath, 50), animation([this](){render();}), dialogBox(true, false)
{
    window.create(sf::VideoMode(1000, 750), "Welcome to RISC-Y Business", sf::Style::Close);
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - window.getSize().x / 2, sf::VideoMode::getDesktopMode().height / 2 - window.getSize().y / 2));
    window.setFramerateLimit(60);

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
    title.setString("RISC-Y Business");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::Black);
    title.setPosition(logoPosition.x, logoPosition.y + logoSize.y + 20);

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
}

void StartScreen::run()
{
    while (window.isOpen())
    {
        update();
        render();
    }
}

void StartScreen::update()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        // - - - - - - -
        switch (event.type) //Switch events
        {
            default:
                break;
            // - - - - - - -
            case sf::Event::Closed:
                clickSound.playSoundEffect();
                window.close();
                break;
            // - - - - - - -
            case sf::Event::MouseButtonPressed: //Switch mouse button pressed events
                switch (event.mouseButton.button)
                {
                    case sf::Mouse::Left:
                        switch (MouseUtilities::isMouseInRectangle(openButtonPosition, buttonSize, &window))
                        {
                            case true:
                                clickSound.playSoundEffect();
                                dialogBox.toggleTextbox(false);
                                temp = dialogBox.run("Open Project", "");
                                if (temp != "")
                                {
                                    ide.setProject(temp);
                                    window.close();
                                    ide.run();
                                }
                                break;

                            case false:
                                break;
                        }

                        switch (MouseUtilities::isMouseInRectangle(newButtonPosition, buttonSize, &window))
                        {
                            case true:
                                clickSound.playSoundEffect();
                                dialogBox.toggleTextbox(true);
                                temp = dialogBox.run("Create Project", "");
                                if (temp != "")
                                {
                                    ide.setProject(temp);
                                    window.close();
                                    ide.run();
                                }
                                break;

                            case false:
                                break;
                        }

                        break;
                    
                    case sf::Mouse::Right:
                        break;

                    default:
                        break;
                }
                break;

            case sf::Event::KeyPressed:
                switch (event.key.code) //Switch key pressed events
                {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;

                    case sf::Keyboard::O:
                        clickSound.playSoundEffect();
                        dialogBox.toggleTextbox(false);
                        temp = dialogBox.run("Open Project", "");
                        if (temp != "")
                        {
                            ide.setProject(temp);
                            window.close();
                            ide.run();
                        }
                        break;

                    case sf::Keyboard::N:
                        clickSound.playSoundEffect();
                        dialogBox.toggleTextbox(true);
                        temp = dialogBox.run("Create Project", "");
                        if (temp != "")
                        {
                            ide.setProject(temp);
                            window.close();
                            ide.run();
                        }
                        break;

                    default:
                        break;
                }
                break;

            case sf::Event::MouseMoved:
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                switch(MouseUtilities::isMouseInRectangle(openButtonPosition, buttonSize, &window)) 
                {
                    case true:
                        switch(animatingOpenButton)
                        {
                            case false:
                                animation.scale(openSprite, sf::Vector2f(1, 1), sf::Vector2f(1.1, 1.1), 0.1);
                                animatingOpenButton = true;
                                break;
                            case true:
                                break;
                        }
                        break;

                    case false:
                        switch(animatingOpenButton)
                        {
                            case true:
                                animation.scale(openSprite, sf::Vector2f(1.1, 1.1), sf::Vector2f(1, 1), 0.1);
                                animatingOpenButton = false;
                                break;
                            case false:
                                break;
                        }
                        break;
                }
                switch(MouseUtilities::isMouseInRectangle(newButtonPosition, buttonSize, &window))
                {
                    case true:
                        switch(animatingNewButton)
                        {
                            case false:
                                animation.scale(newSprite, sf::Vector2f(1, 1), sf::Vector2f(1.1, 1.1), 0.1);
                                animatingNewButton = true;
                                break;
                            case true:
                                break;
                        }
                        break;

                    case false:
                        switch(animatingNewButton)
                        {
                            case true:
                                animation.scale(newSprite, sf::Vector2f(1.1, 1.1), sf::Vector2f(1, 1), 0.1);
                                animatingNewButton = false;
                                break;
                            case false:
                                break;
                        }
                        break;
                }
                break;
        }
    }
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
