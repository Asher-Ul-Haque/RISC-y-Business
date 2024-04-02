#ifndef EDITOR_H
#define EDITOR_H
#include <SFML/Graphics.hpp>
#include "../../../include/utility/soundUtilities.h"
#include "../../../include/utility/mouseUtilities.h"
#include "../../../include/utility/animationUtilities.h"

// - - - - - - - -

class TextEditor;

class IDE 
{

    int screenWidth = 1920;
    int screenHeight = 1080;
    sf::Color backgroundColor = sf::Color(239, 239, 239, 255);

    sf::RenderWindow window;
    //TextEditor* textEditor;
    sf::Font font;
    sf::Text title;
    sf::Texture topBarTexture;
    sf::Texture buttonTextures[4];
    sf::Sprite buttons[4];

    std::string textureDirectoryPath = "../../include/resources/textures/";
    std::string fontDirectoryPath = "../../include/resources/fonts/";
    std::string soundDirectoryPath = "../../include/resources/sounds/";
    std::string projectDirectoryPath;
    // - - - - - - - -
    std::string topBarTexturePath = "topbar.png";
    std::string buttonTexturePaths[4] = {"run.png", "simulate.png", "assemble.png", "save.png"};

    sf::RectangleShape topBar;
    sf::RectangleShape lineNumbers;
    sf::RectangleShape files;
    sf::Sprite fileButtons[3];
    std::string fileButtonsTexturePath[3] = {"assemblyButton.png", "binaryButton.png", "reportButton.png"};
    sf::Texture fileButtonsTextures[3];
    bool buttonClickable[3] = {true, false, false};
    
    sf::Text hoverText;
    bool showText = false;
    sf::Sprite hoverBox;
    sf::Texture hoverBoxTexture;
    std::string hoverBoxTexturePath = "hoverBox.png";
    std::string hoverTexts[4] = {"Run", "Execute", "Assemble", "Save"};

    SoundUtilities soundEffects;
    AnimationUtilities animation;

    bool isAnimating[4] = {false, false, false, false};
    
    
public:
    IDE();
    void setProject(std::string PROJECTPATH);
    void run();
    void update();
    void render();
    void handleEvents();
};

// - - - - - - - -

#endif // EDITOR_H
