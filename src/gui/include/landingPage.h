#ifndef LANDING_PAGE_H
#define LANDING_PAGE_H
#include <SFML/Graphics.hpp>

// - - - - - - - - - - - - - - - - -
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 100
#define TEXTURE_DIRECTORY "../assets/textures/landingPage/"
#define FONT_DIRECTORY "../assets/fonts/landingPage/"

typedef struct
{
    sf::RectangleShape rect;
    sf::Texture texture;
    unsigned int x;
    unsigned int y;
    bool isPressed;
    bool isHovered;
} Button;

typedef struct
{
    sf::RenderWindow window;
    Button* openExistingButton;
    Button* openNewButton;
    sf::Vector2i mousePosition;
} LandingPage;

Button* createButton(unsigned int X, unsigned int Y, const char *TEXTURE__PATH);

bool isButtonHovered(Button *BUTTON, LandingPage *LANDING__PAGE);

bool isButtonPressed(Button *BUTTON, LandingPage *LANDING__PAGE);

void handleButtonHover(Button *BUTTON, LandingPage *LANDING__PAGE);

void handleButtonPress(Button *BUTTON, LandingPage *LANDING__PAGE);

void render(LandingPage *LANDING__PAGE);

void update();

void handleEvents(LandingPage *LANDING__PAGE);

// - - - - - - - - - - - - - - - - -
#endif // LANDING_PAGE_H
