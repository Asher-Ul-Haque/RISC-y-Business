#include "editor.h"
#include <iostream>
#include <filesystem>
#include <fstream>

IDE::IDE() 
    : soundEffects(soundDirectoryPath + "click.wav", 50),
    animation([this](){render();})
{
    if (!font.loadFromFile(fontDirectoryPath + "JetBrainsMono-Light.ttf"))
    {
        std::cout << "Error loading JetBrainsMono-ExtraBold.ttf" << std::endl;
    }

    title.setFont(font);
    title.setCharacterSize(16);
    title.setFillColor(sf::Color::White);    
    if (!hoverBoxTexture.loadFromFile(textureDirectoryPath + hoverBoxTexturePath))
    {
        std::cout << "Error loading " << hoverBoxTexturePath << std::endl;
    }
    hoverBox.setTexture(hoverBoxTexture);
    hoverBoxTexture.setSmooth(true);
    hoverText.setFont(font);
    hoverText.setCharacterSize(12);
    hoverText.setFillColor(sf::Color::White);

    statusText.setFont(font);
    statusText.setCharacterSize(15);
    statusText.setFillColor(colors[!backgroundColor]);

    for (int i = 0; i < 5; i++)
    {
        if (!buttonTextures[i].loadFromFile(textureDirectoryPath + buttonTexturePaths[i]))
        {
            std::cout << "Error loading " << buttonTexturePaths[i] << std::endl;
        }
        buttonTextures[i].setSmooth(true);
        
        buttons[i].setTexture(buttonTextures[i]);
        buttons[i].setOrigin(buttonTextures[i].getSize().x / 2, buttonTextures[i].getSize().y / 2);
        buttons[i].setPosition(screenWidth - 50 * (i + 1) - 50, 25);
        buttons[i].setScale(1.2, 1.2);
    }
    
    topBarTexture.loadFromFile(textureDirectoryPath + topBarTexturePath);
    topBar.setTexture(&topBarTexture);
    topBar.setSize(sf::Vector2f(screenWidth, 50));
    topBar.setOutlineThickness(1);
    topBar.setOutlineColor(sf::Color::White);
    topBar.setPosition(0, 0);
    
    lineNumbers.setSize(sf::Vector2f(1, screenHeight));
    lineNumbers.setFillColor(sf::Color(135, 136, 140));
    lineNumbers.setPosition(45, 50);
    lineNumbers.setOutlineColor(sf::Color(135, 136, 140));
    lineNumbers.setOutlineThickness(2);

    bottomBar.setSize(sf::Vector2f(screenWidth, 20));
    bottomBar.setPosition(0, screenHeight - 40);
    bottomBar.setFillColor(colors[backgroundColor]);
    bottomBar.setOutlineThickness(2);
    bottomBar.setOutlineColor(sf::Color(135, 136, 140));

    statusText.setPosition(bottomBar.getPosition() + sf::Vector2f(20, 0));

    for (int i = 0; i < 3; ++i)
    {
        if (!fileButtonsTextures[i].loadFromFile(textureDirectoryPath + fileButtonsTexturePath[i]))
        {
            std::cout << "Failed to load: " << fileButtonsTexturePath[i] << std::endl;
        }
        fileButtonsTextures[i].setSmooth(true);
        fileButtons[i].setTexture(fileButtonsTextures[i]);
    }

    for (int i = 0; i < 3; ++i)
    {
        fileButtons[i].setOrigin(fileButtonsTextures[i].getSize().x / 2, fileButtonsTextures[i].getSize().y / 2);
    }
    fileButtons[0].setPosition(70, 30);
    fileButtons[1].setPosition(190, 30);
    fileButtons[2].setPosition(337, 30);

    textEditor = TextEditorUtilities(&window, screenWidth, screenHeight);
}

void IDE::render()
{
    window.clear(colors[backgroundColor]);
    textEditor.render();
    window.setView(window.getDefaultView()); // Reset view to window coordinates
    window.draw(lineNumbers);
    window.draw(topBar);
    window.draw(title);
    for (int i = 0; i < 5; i++)
    {
        window.draw(buttons[i]);
    }
    for (int i = 0; i < 3; ++i)
    {
        switch(buttonClickable[i])
        {
            case true:
                window.draw(fileButtons[i]);
                break;

            case false:
                break;
        }
    }
    if (showText)
    {
        window.draw(hoverBox);
        window.draw(hoverText);
    }
    window.draw(bottomBar);
    window.draw(statusText);

    window.display();
}

void IDE::update()
{
    statusText.setString(textEditor.getStatus());
    sf::Event event;
    while (window.pollEvent(event))
    {
        textEditor.update(&event);
        switch (event.type)
        {
            default:
                break;

            case sf::Event::Closed:
                soundEffects.setPath(soundDirectoryPath + "failure.wav");
                soundEffects.playSoundEffect();
                window.close();
                break;

            case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                    case sf::Keyboard::Escape:
                        soundEffects.setPath(soundDirectoryPath + "failure.wav");
                        soundEffects.playSoundEffect();
                        window.close();
                        break;

                    default:
                        soundEffects.setPath(soundDirectoryPath + "keypress.wav");
                        soundEffects.playSoundEffect();
                        break;
                }
                break;

            case sf::Event::MouseButtonPressed:
                switch(event.mouseButton.button)
                {
                    case sf::Mouse::Left:
                        for (int i = 0; i < 5; ++i)
                        {
                            switch (MouseUtilities::isMouseInRectangle(buttons[i].getPosition(), sf::Vector2f(buttonTextures[i].getSize().x, buttonTextures[i].getSize().y), &window))
                            {
                                case true:
                                    switch (i)
                                    {
                                        case 4:
                                            textEditor.writeToFile();
                                            break;

                                        case 0:
                                            switchColors();
                                            break;

                                        default:
                                            break;

                                    }
                                    soundEffects.playSoundEffect();
                                    break;

                                case false:
                                    break;
                            }
                        }

                        for (int i = 0; i < 3; ++i)
                        {
                            switch (MouseUtilities::isMouseInRectangle(fileButtons[i].getPosition(), sf::Vector2f(fileButtonsTextures[i].getSize().x, fileButtonsTextures[i].getSize().y), &window))
                            {
                                case true:
                                    soundEffects.playSoundEffect();
                                    fileButtonAnimation[i] = false;
                                    currentFile = i;
                                    textEditor.writeToFile();
                                    currentFilePath = projectDirectoryPath + "/" + projectFiles[i];
                                    textEditor.setFilePath(currentFilePath);
                                    textEditor.readFromFile();
                                    animation.scale(fileButtons[i], sf::Vector2f(1.05, 1.05), sf::Vector2f(1, 1), 0.1);
                                    break;

                                case false:
                                    break;
                            }
                        }

                        default:
                            break;
                }

            case sf::Event::MouseMoved:
                for (int i = 0; i < 3; ++i)
                {
                    switch(buttonClickable[i])
                    {
                        case true:
                            switch (MouseUtilities::isMouseInRectangle(fileButtons[i].getPosition(), sf::Vector2f(fileButtonsTextures[i].getSize().x, fileButtonsTextures[i].getSize().y), &window))
                            {
                                case true:
                                    switch(fileButtonAnimation[i])
                                    {
                                        case false:
                                            animation.scale(fileButtons[i], sf::Vector2f(1, 1), sf::Vector2f(1.05, 1.05), 0.1);
                                            fileButtonAnimation[i] = true;
                                            break;

                                        case true:
                                            break;
                                    }
                                break;

                                case false:
                                    switch(fileButtonAnimation[i])
                                    {
                                        case true:
                                            animation.scale(fileButtons[i], sf::Vector2f(1.05, 1.05), sf::Vector2f(1, 1), 0.1);
                                            fileButtonAnimation[i] = false;
                                            break;

                                        case false:
                                            break;
                                    }
                                break;
                            }
                            break;
                        
                        case false:
                            break;
                    }
                }

                for (int i = 0; i < 5; ++i)
                {
                    switch (MouseUtilities::isMouseInRectangle(buttons[i].getPosition(), sf::Vector2f(buttonTextures[i].getSize().x, buttonTextures[i].getSize().y), &window))
                    {
                        case true:
                            switch(isAnimating[i])
                            {
                                case false:
                                    animation.scale(buttons[i], sf::Vector2f(1.2, 1.2), sf::Vector2f(1.5, 1.5), 0.1);
                                    isAnimating[i] = true;
                                    hoverText.setString(hoverTexts[i]);
                                    hoverBox.setPosition(buttons[i].getPosition().x - hoverBoxTexture.getSize().x/2, buttons[i].getPosition().y + buttonTextures[i].getSize().y/2 + 20);
                                    hoverText.setPosition(hoverBox.getPosition().x + hoverBoxTexture.getSize().x/2 - hoverText.getLocalBounds().width/2, hoverBox.getPosition().y - hoverText.getLocalBounds().height/2 + 10);
                                    showText = true;
                                    break;

                                case true:
                                    break;
                            }
                            break;

                        case false:
                            switch(isAnimating[i])
                            {
                                case true:
                                    animation.scale(buttons[i], sf::Vector2f(1.5, 1.5), sf::Vector2f(1.2, 1.2), 0.1);
                                    isAnimating[i] = false;
                                    showText = false;
                                    break;

                                case false:
                                    break;
                            }
                            break;
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

void IDE::setProject(std::string PROJECTPATH)
{
    projectDirectoryPath = PROJECTPATH;
    title.setString(projectDirectoryPath);
    title.setPosition((screenWidth - title.getGlobalBounds().width) / 2, 15);

    window.create(sf::VideoMode::getDesktopMode(), "RISC-Y Business", sf::Style::Default);
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - window.getSize().x / 2, sf::VideoMode::getDesktopMode().height / 2 - window.getSize().y / 2));
    window.setFramerateLimit(60);
    sf::Texture logoTexture;
    if (!logoTexture.loadFromFile(textureDirectoryPath + "logo.png"))
    {
        std::cout << "Error loading logo.png" << std::endl;
    }
    logoTexture.setSmooth(true);
    window.setIcon(logoTexture.getSize().x, logoTexture.getSize().y, logoTexture.copyToImage().getPixelsPtr());

    for (const auto& entry : std::filesystem::directory_iterator(projectDirectoryPath)) 
    {
        std::string filename = entry.path().filename().string();
        for (int i = 0; i < 3; ++i)
        {
            switch(filename == fileButtonsTexturePath[i])
            {
                case true:
                    buttonClickable[i] = true;
                    break;

                case false:
                    break;
            }
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        if (!std::filesystem::exists(projectDirectoryPath + "/" + projectFiles[i]))
        {
            std::ofstream output(projectDirectoryPath + "/" + projectFiles[i]);
        }
    }
    std::string assemblyFilePath = projectDirectoryPath + "/" + projectFiles[0];
    textEditor.setFilePath(assemblyFilePath);
    textEditor.readFromFile();
}

void IDE::switchColors()
{
    backgroundColor = !backgroundColor;
    std::cout << "New color Scheme: " + std::to_string(backgroundColor) << std::endl;
    bottomBar.setFillColor(colors[backgroundColor]);
    statusText.setFillColor(colors[!backgroundColor]);
}