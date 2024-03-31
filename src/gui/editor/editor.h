#ifndef IDE_H
#define IDE_H
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

    std::string textureDirectoryPath = "../../../include/resources/textures/";
    std::string fontDirectoryPath = "../../../include/resources/fonts/";
    std::string soundDirectoryPath = "../../../include/resources/sounds/";
    // - - - - - - - -
    std::string titleText = "RISC-Y Business";
    std::string topBarTexturePath = "topbar.png";
    std::string buttonTexturePaths[4] = {"run.png", "simulate.png", "assemble.png", "save.png"};

    sf::RectangleShape topBar;
    sf::RectangleShape lineNumbers;

    SoundUtilities soundEffects;
    AnimationUtilities animation;

    bool isAnimating[4] = {false, false, false, false};
    
public:
    IDE();
    void run();
    void update();
    void render();
    void handleEvents();
};

// - - - - - - - -

#endif // IDE_H
