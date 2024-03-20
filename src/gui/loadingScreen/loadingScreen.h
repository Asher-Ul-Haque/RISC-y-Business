#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H
#include <SFML/Graphics.hpp>
// - - - - - - - - -

class LoadingScreen
{
    public:
        LoadingScreen();
        void run();
    
    private:
        sf::Color backgroundColor = sf::Color(255, 255, 255, 255);
        // - - - - - -  - - -
        std::string textureDirectoryPath = "../../include/resources/textures/";
        std::string fontDirectoryPath = "../../include/resources/fonts/";
        // - - - - - -  - - -
        sf::Vector2f logoPosition = sf::Vector2f(223, 50);
        sf::Vector2f logoSize = sf::Vector2f(204, 188);
        sf::Texture logoTexture;
        sf::Sprite logoSprite;
        sf::Text title;
        sf::Font font;
        // - - - - - - -
        sf::RenderWindow window;
        // - - - - - - -
        void update();
        void render();
};

#endif // LOADINGSCREEN_H

