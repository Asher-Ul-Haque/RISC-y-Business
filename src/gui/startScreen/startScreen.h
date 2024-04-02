#ifndef STARTSCREEN_H
#define STARTSCREEN_H
#include "../../../include/utility/mouseUtilities.h"
#include "../../../include/utility/soundUtilities.h"
#include "../../../include/utility/animationUtilities.h"
#include "../dialogBox/dialogBox.h"
#include "../editor/editor.h"
// - - - - - - - - -

class StartScreen 
{
    public:
        StartScreen();
        void run();

    private:
        // - - - - - -  - - -
        sf::Color backgroundColor = sf::Color(255, 255, 255, 255);
        int screenWidth = 1000;
        int screenHeight = 750;
        int iconWidth = 521;
        int iconHeight = 479;
        float slideInDuration = 0.5f;
        // - - - - - -  - - -
        std::string textureDirectoryPath = "../../include/resources/textures/";
        std::string fontDirectoryPath = "../../include/resources/fonts/";
        std::string soundDirectoryPath = "../../include/resources/sounds/";
        // - - - - - -  - - -
        sf::Vector2f buttonSize = sf::Vector2f(403, 72);
        sf::Vector2f openButtonPosition = sf::Vector2f(299 + buttonSize.x/2, 510 + buttonSize.y/2);
        sf::Vector2f newButtonPosition = sf::Vector2f(299 + buttonSize.x/2, 370 + buttonSize.y/2);
        sf::Sprite openSprite;
        sf::Sprite newSprite;
        sf::Texture openTexture;
        sf::Texture newTexture;
        // - - - - - - - 
        sf::Vector2f logoSize = sf::Vector2f(204, 188);
        sf::Vector2f logoPosition = sf::Vector2f(screenWidth/2 - logoSize.x/2 , 50);
        sf::Texture logoTexture;
        sf::Sprite logoSprite;
        sf::Text title;
        sf::Font font;
        // - - - - - - -
        sf::RenderWindow window;
        // - - - - - - -
        std::string clickSoundFilePath = "click.wav";
        SoundUtilities clickSound;
        // - - - - - - -
        AnimationUtilities animation;
        bool wasMouseInsideOpenButton = false;
        bool wasMouseInsideNewButton = false;
        bool animatingNewButton = false;
        bool animatingOpenButton = false;
        std::string temp;
        // - - - - - - -
        DialogBox dialogBox;
        IDE ide;
        // - - - - - - -
        void update();
        void render();
};

#endif // STARTSCREEN_H
