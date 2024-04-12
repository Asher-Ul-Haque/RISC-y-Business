#ifndef EDITOR_H
#define EDITOR_H
#include <SFML/Graphics.hpp>
#include "../../../include/utility/soundUtilities.h"
#include "../../../include/utility/mouseUtilities.h"
#include "../../../include/utility/animationUtilities.h"
#include "../../../include/utility/textEditorUtilities.h"

// - - - - - - - -

class IDE 
{

    int screenWidth = sf::VideoMode::getDesktopMode().width;
    int screenHeight = sf::VideoMode::getDesktopMode().height;
    sf::Color backgroundColor = sf::Color(239, 239, 239, 255);

    sf::RenderWindow window;
    TextEditorUtilities textEditor;
    sf::Font font;
    sf::Text title;
    sf::Texture topBarTexture;
    sf::Texture buttonTextures[4];
    sf::Sprite buttons[4];

    std::string textureDirectoryPath = "../../include/resources/textures/";
    std::string fontDirectoryPath = "../../include/resources/fonts/";
    std::string soundDirectoryPath = "../../include/resources/sounds/";
    std::string projectDirectoryPath;
    std::string projectFiles[3] = {"assembly.asm", "binary.bin", "simulatorReport.txt"};
    // - - - - - - - -
    std::string topBarTexturePath = "topbar.png";
    std::string buttonTexturePaths[4] = {"run.png", "simulate.png", "assemble.png", "save.png"};

    sf::RectangleShape topBar;
    sf::RectangleShape lineNumbers;
    sf::Sprite fileButtons[3];
    std::string fileButtonsTexturePath[3] = {"assemblyButton.png", "binaryButton.png", "reportButton.png"};
    sf::Texture fileButtonsTextures[3];
    bool fileButtonAnimation[3] = {true, true, true};
    bool buttonClickable[3] = {true, true, true};
    unsigned short currentFile = 0;
    std::string currentFilePath;
    
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
