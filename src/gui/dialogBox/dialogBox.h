#ifndef DIALOGBOX_H
#define DIALOGBOX_H
#include "../../../include/utility/soundUtilities.h"
#include "../../../include/utility/mouseUtilities.h"
#include "../../../include/utility/animationUtilities.h"
#include "../../../include/utility/menuUtilities.h"
// - - - - - - - - -

class DialogBox
{
    public:
        DialogBox(bool TEXTBOX, bool DROPDOWN);
        std::string run(std::string TITLE);
        void toggleTextbox(bool TOGGLE);

    private:
        int screenWidth = 650;
        int screenHeight = 400;
        sf::Color backgroundColor = sf::Color(255, 255, 255, 255);
        // - - - - - - - - -
        std::string projectDirectoryPath;
        std::string textureDirectoryPath = "../../include/resources/textures/";
        std::string fontDirectoryPath = "../../include/resources/fonts/";
        std::string soundDirectoryPath = "../../include/resources/sounds/";
        std::string successSoundFilePath = "success.wav";
        std::string failureSoundFilePath = "failure.wav";
        std::string cancelTextureFilePath = "cancel.png";
        std::string okTextureFilePath = "ok.png";
        // - - - - - - - - -
        sf::Vector2f buttonSize = sf::Vector2f(151, 61);
        //The ok button is at the bottom right
        sf::Vector2f okButtonPosition = sf::Vector2f(screenWidth - 60, screenHeight - 30);
        sf::Vector2f cancelButtonPosition = okButtonPosition - sf::Vector2f(110, 0);
        sf::Sprite okSprite;
        sf::Sprite cancelSprite;
        sf::Texture okTexture;
        sf::Texture cancelTexture;
        // - - - - - - - 
        sf::Vector2f logoSize = sf::Vector2f(204, 188);
        sf::Vector2f logoPosition = sf::Vector2f(screenWidth/2 - logoSize.x/2 , 15);
        sf::Texture logoTexture;
        sf::Sprite logoSprite;
        sf::Text text;
        sf::Font font;
        // - - - - - - -
        sf::RectangleShape divider;
        // - - - - - - -
        sf::RenderWindow window;
        // - - - - - - -
        SoundUtilities soundEffects;
        // - - - - - - -
        bool textbox;
        bool dropdown;
        // - - - - - - -
        AnimationUtilities animation;
        bool animatingOkButton = false;
        bool animatingCancelButton = false;
        // - - - - - - -
        void update();
        void render();
        void createWindow(std::string TITLE);
        void createProject();
        // - - - - - - -
        TextBox textBox;
        DropDown dropDown;
}; 

// - - - - - - - - -
#endif // DIALOGBOX_H
