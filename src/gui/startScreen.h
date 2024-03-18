#ifndef STARTSCREEN_H
#define STARTSCREEN_H
#include <SFML/Graphics.hpp>

class StartScreen 
{
    public:

        StartScreen();
        void run();

    private:

        sf::Color backgroundColor = sf::Color(255, 255, 255, 255);
        std::string textureDirectoryPath = "../../include/textures/";
        std::string fontDirectoryPath = "../../include/fonts/";
        sf::Vector2f buttonSize = sf::Vector2f(403, 72);
        sf::Vector2f backgroundSize = sf::Vector2f(1000, 700);
        //Logo position
        sf::Vector2f logoPosition = sf::Vector2f(398, 50);
        //Logo size
        sf::Vector2f logoSize = sf::Vector2f(204, 188);
        sf::Vector2f openButtonPosition = sf::Vector2f(299 + buttonSize.x/2, 510 + buttonSize.y/2);
        sf::Vector2f newButtonPosition = sf::Vector2f(299 + buttonSize.x/2, 370 + buttonSize.y/2);
        sf::RenderWindow window;
        sf::Texture logoTexture;
        sf::Sprite logoSprite;
        sf::Texture openTexture;
        sf::Sprite openSprite;
        sf::Texture newTexture;
        sf::Text title;
        sf::Sprite newSprite;
        sf::Font font;
        bool isMouseOverOpenButton = false;
        bool isMouseOverNewButton = false;
        void processEvents();
        void update();
        void render();

        bool isMouseOverButton(sf::Vector2f buttonPosition, sf::Vector2f buttonSize, sf::Vector2i mousePosition);
};

#endif // STARTSCREEN_H
