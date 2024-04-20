#include "dialogBox.h"
#include <filesystem>
#include <iostream>

DialogBox::DialogBox(bool TEXTBOX, bool DROPDOWN) 
    : 
    soundEffects(soundDirectoryPath + successSoundFilePath, 50), 
    animation([this](){render();}), 
    textBox(&window, sf::Vector2f(325, 250)), 
    dropDown(&window, sf::Vector2f(325, 220))
{
    textbox = TEXTBOX;
    dropdown = DROPDOWN;
    std::cout << "Hello WOrld" << std::endl;
}

std::string DialogBox::run(std::string TITLE, std::string MESSAGE)
{
    createWindow(TITLE);
    text.setFillColor(sf::Color::Red);
    std::string result;
    int count = 0;
    int lastSpace = 0;

    for (int i = 0; i < MESSAGE.length(); ++i) 
    {
        char ch = MESSAGE[i];
        result += ch;
        count++;

        if (ch == ' ') 
        {
            lastSpace = i; 
        }

        if (count == 40 && lastSpace != -1) 
        {
            result[lastSpace] = '\n';
            count = i - lastSpace;
            lastSpace = -1;
        }
    }

    text.setString(result);
    text.setPosition((screenWidth - text.getGlobalBounds().width) / 2, screenHeight / 2 + 30);
    while (window.isOpen())
    {
        update();
        window.clear(sf::Color(239, 239, 239, 255));
        if (textbox)
        {
            textBox.render();
        }
        else if (dropdown)
        {
            dropDown.render();
        }
        render();
        window.display();
    }
    return projectDirectoryPath;
}

void DialogBox::update()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (textbox)
        {
            textBox.handleInput(&event);
        }
        if (dropdown)
        {
            dropDown.handleInput(&event);
        }
        switch (event.type) //Switch events
        {
            default:
                break;
            // - - - - - - -
            case sf::Event::Closed:
                soundEffects.setPath(soundDirectoryPath + failureSoundFilePath);
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
                                createProject();
                                break;

                            case false:
                                break;
                        }

                        switch (MouseUtilities::isMouseInRectangle(cancelButtonPosition, buttonSize, &window))
                        {
                            case true:
                                soundEffects.setPath(soundDirectoryPath + failureSoundFilePath);
                                soundEffects.playSoundEffect();
                                window.close();
                                projectDirectoryPath = "";
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

                    case sf::Keyboard::Return:
                        createProject();
                        break;

                    case sf::Keyboard::N:
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
    if (!dropdown && !textbox)
    {
        window.draw(text);
    }
    window.draw(logoSprite);
    window.draw(okSprite);
    window.draw(cancelSprite);
    window.draw(divider);
    window.display();
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
    text.setFillColor(sf::Color::Red);
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
    divider.setPosition(0, okButtonPosition.y - 30);
}

void DialogBox::createProject()
{
    std::string projectsDirectory = std::getenv("HOME");
    projectsDirectory += "/RISCY Projects/";
    projectDirectoryPath = projectsDirectory + textBox.getInput();
    if (std::filesystem::exists(projectDirectoryPath) && textbox)
    {
        textBox.error();
        return;
    }
    if (!std::filesystem::create_directory(projectDirectoryPath) && textbox) 
    {
        textBox.error();
        return;
    }
    soundEffects.setPath(soundDirectoryPath + successSoundFilePath);
    soundEffects.playSoundEffect();
    if (dropdown)
    {
        projectDirectoryPath =  dropDown.getSelectedOption() == "Select Option" ? "" : projectsDirectory + dropDown.getSelectedOption();
    }
    window.close();
}
