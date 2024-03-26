#include "dialogBox.h"
#include <iostream>

DialogBox::DialogBox(bool TEXTBOX, bool DROPDOWN) : soundEffects(soundDirectoryPath + successSoundFilePath, 50), animation([this](){render();}), textBox(&window, sf::Vector2f(325, 300), sf::Vector2f(400, 50))
{
    textbox = TEXTBOX;
    dropdown = DROPDOWN;
}

void DialogBox::run(std::string TITLE)
{
    createWindow(TITLE);
    while (window.isOpen())
    {
        update();
        render();
        if (textbox)
        {
            textBox.render();
        }
        window.display();
    }
}

void DialogBox::update()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type) //Switch events
        {
            default:
                break;
            // - - - - - - -
            case sf::Event::Closed:
                window.close();
                break;
            // - - - - - - -
            case sf::Event::MouseButtonPressed: //Switch mouse button pressed events
                switch (event.mouseButton.button)
                {
                    case sf::Mouse::Left:
                        switch (MouseUtilities::isMouseInRectangle(okButtonPosition, buttonSize, &window))
                        {
                            case true:
                                soundEffects.setPath(soundDirectoryPath + successSoundFilePath);
                                soundEffects.playSoundEffect();
                                std::cout << "Ok" << std::endl;
                                break;
                            case false:
                                break;
                        }

                        switch (MouseUtilities::isMouseInRectangle(cancelButtonPosition, buttonSize, &window))
                        {
                            case true:
                                soundEffects.setPath(soundDirectoryPath + failureSoundFilePath);
                                soundEffects.playSoundEffectUntilFinished();
                                window.close();
                                break;
                            case false:
                                break;
                        }
                        break;
                    
                    case sf::Mouse::Right:
                        std::cout << "Right mouse button pressed!" << std::endl;
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
                        std::cout << "Ok file" << std::endl;
                        break;

                    case sf::Keyboard::N:
                        std::cout << "Cancel file" << std::endl;
                        break;

                    default:
                        break;
                }
                break;

            case sf::Event::MouseMoved:
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                switch(MouseUtilities::isMouseInRectangle(okButtonPosition, buttonSize, &window)) 
                {
                    case true:
                        switch(animatingOkButton)
                        {
                            case false:
                                animation.scale(okSprite, sf::Vector2f(0.65, 0.65), sf::Vector2f(0.75, 0.75), 0.1);
                                animatingOkButton = true;
                                break;
                            case true:
                                break;
                        }
                        break;

                    case false:
                        switch(animatingOkButton)
                        {
                            case true:
                                animation.scale(okSprite, sf::Vector2f(0.75, 0.75), sf::Vector2f(0.65, 0.65), 0.1);
                                animatingOkButton = false;
                                break;
                            case false:
                                break;
                        }
                        break;
                }
                switch(MouseUtilities::isMouseInRectangle(cancelButtonPosition, buttonSize, &window))
                {
                    case true:
                        switch(animatingCancelButton)
                        {
                            case false:
                                animation.scale(cancelSprite, sf::Vector2f(0.65, 0.65), sf::Vector2f(0.75, 0.75), 0.1);
                                animatingCancelButton = true;
                                break;
                            case true:
                                break;
                        }
                        break;

                    case false:
                        switch(animatingCancelButton)
                        {
                            case true:
                                animation.scale(cancelSprite, sf::Vector2f(0.75, 0.75), sf::Vector2f(0.65, 0.65), 0.1);
                                animatingCancelButton = false;
                                std::cout << "Heiya" << std::endl;
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

void DialogBox::render()
{
    window.clear(sf::Color(239, 239, 239, 255));
    window.draw(logoSprite);
    window.draw(text);
    window.draw(okSprite);
    window.draw(cancelSprite);
    window.draw(divider);
}

void DialogBox::toggleTextbox(bool TOGGLE)
{
    textbox = TOGGLE;
    dropdown = !TOGGLE;
}

void DialogBox::createWindow(std::string TITLE)
{
    window.create(sf::VideoMode(screenWidth, screenHeight), TITLE, sf::Style::Close);
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - window.getSize().x / 2, sf::VideoMode::getDesktopMode().height / 2 - window.getSize().y / 2));
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    if (!logoTexture.loadFromFile(textureDirectoryPath + "logo.png"))
    {
        std::cout << "Error loading logo.png" << std::endl;
    }
    logoTexture.setSmooth(true);
    window.setIcon(logoTexture.getSize().x, logoTexture.getSize().y, logoTexture.copyToImage().getPixelsPtr());
    // - - - - - - - - -
    font.loadFromFile(fontDirectoryPath + "JetBrainsMono-Bold.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    // - - - - - - - - -
    logoTexture.loadFromFile(textureDirectoryPath + "logo.png");
    logoSprite.setTexture(logoTexture);
    logoSprite.setPosition(logoPosition);
    logoSprite.setScale(logoSize.x / logoTexture.getSize().x, logoSize.y / logoTexture.getSize().y);
    // - - - - - - - - -
    okTexture.loadFromFile(textureDirectoryPath + okTextureFilePath);
    okTexture.setSmooth(true);
    okSprite.setTexture(okTexture);
    okSprite.setPosition(okButtonPosition);
    okSprite.setScale(0.65, 0.65);
    okSprite.setOrigin(buttonSize.x / 2, buttonSize.y / 2);
    // - - - - - - - - -
    cancelTexture.loadFromFile(textureDirectoryPath + cancelTextureFilePath);
    cancelTexture.setSmooth(true);
    cancelSprite.setTexture(cancelTexture);
    cancelSprite.setPosition(cancelButtonPosition);
    cancelSprite.setScale(0.65, 0.65);
    cancelSprite.setOrigin(buttonSize.x / 2, buttonSize.y / 2);
    // - - - - - - - - -
    divider.setSize(sf::Vector2f(screenWidth, 2));
    divider.setFillColor(sf::Color(208, 224, 240));
    divider.setPosition(0, okButtonPosition.y - 30);;
    // - - - - - - - - -

}
