#ifndef DIALOGBOX_H
#define DIALOGBOX_H
#include "../../../include/utility/soundUtilities.h"
#include "../../../include/utility/mouseUtilities.h"
// - - - - - - - - -

class DialogBox
{
    public:
        DialogBox(bool Textbox, bool Dropdown);
        void run();

    private:
        sf::Color backgroundColor = sf::Color(255, 255, 255, 255);
        // - - - - - - - - -
        std::string textureDirectoryPath = "../../include/resources/textures/";
        std::string fontDirectoryPath = "../../include/resources/fonts/";
        std::string soundDirectoryPath = "../../include/resources/sounds/";
        std::string successSoundFilePath = "success.wav";
        std::string failureSoundFilePath = "failure.wav";
        std::string cancelTextureFilePath = "cancel.png";
        std::string okTextureFilePath = "ok.png";
        // - - - - - - - - -
        sf::Vector2f buttonSize = sf::Vector2f(403, 72);
        sf::Vector2f openButtonPosition = sf::Vector2f(299 + buttonSize.x/2, 510 + buttonSize.y/2);
        sf::Vector2f newButtonPosition = sf::Vector2f(299 + buttonSize.x/2, 370 + buttonSize.y/2);
        sf::Sprite okSprite;
        sf::Sprite cancelSprite;
        sf::Texture okTexture;
        sf::Texture canelTexture;
        // - - - - - - - 
        sf::Vector2f logoPosition = sf::Vector2f(398, 50);
        sf::Vector2f logoSize = sf::Vector2f(204, 188);
        sf::Texture logoTexture;
        sf::Sprite logoSprite;
        sf::Text text;
        sf::Font font;
        // - - - - - - -
        sf::RenderWindow window;
        // - - - - - - -
        SoundUtilities soundEffects;
        // - - - - - - -
        bool textbox;
        bool dropdown;
        // - - - - - - -
        void update();
        void render();
}; 

// - - - - - - - - -
#endif // DIALOGBOX_H
