#include "../include/landingPage.h"
// - - - - - - - - - - - - - - - - -

Button* createButton(unsigned int X, unsigned int Y, const char *TEXTURE__PATH)
{
    Button *button = new Button;
    if (button == NULL)
    {
        perror("Error allocating memory for button");
        exit(1);
    }
    if (!button->texture.loadFromFile(TEXTURE__PATH))
    {
        perror("Error loading texture from file");
        free(button);
        exit(1);
    }
    button->rect.setSize(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
    button->rect.setPosition(X, Y);
    button->rect.setTexture(&button->texture, true);
    button->x = X;
    button->y = Y;
    button->isPressed = false;
    button->isHovered = false;

    return button;
}

// - - - - - - - - - - - - - - - - 

bool isButtonHovered(Button *BUTTON, LandingPage *LANDING__PAGE)
{
    if (BUTTON->x < LANDING__PAGE->mousePosition.x && LANDING__PAGE->mousePosition.x < BUTTON->x + BUTTON_WIDTH && BUTTON->y < LANDING__PAGE->mousePosition.y && LANDING__PAGE->mousePosition.y < BUTTON->y + BUTTON_HEIGHT)
    {
        BUTTON->isHovered = true;
        return true;
    }
    BUTTON->isHovered = false;
    return false;
}

// - - - - - - - - - - - -

bool isButtonPressed(Button *BUTTON, LandingPage *LANDING__PAGE)
{
    if (BUTTON->isHovered && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        BUTTON->isPressed = true;
        return true;
    }
    BUTTON->isPressed = false;
    return false;
}

// - - - - - - - - - - -

void handleButtonHover(Button *BUTTON, LandingPage *LANDING__PAGE)
{
    if (BUTTON->isHovered)
    {
        BUTTON->rect.setFillColor(sf::Color(255, 255, 255, 100));
    }
    else
    {
        BUTTON->rect.setFillColor(sf::Color(255, 255, 255, 255));
    }
}

// - - - - - - - - - - -

void handleButtonPress(Button *BUTTON, LandingPage *LANDING__PAGE)
{
    if (BUTTON == LANDING__PAGE->openExistingButton)
    {
        printf("Open existing button pressed\n");
    }
    else if (BUTTON == LANDING__PAGE->openNewButton)
    {
        printf("Open new button pressed\n");
    }
}

// - - - - - - - - - - -

void render(LandingPage *LANDING__PAGE)
{
    LANDING__PAGE->window.clear(sf::Color(0, 0, 0, 255));
    LANDING__PAGE->window.draw(LANDING__PAGE->openExistingButton->rect);
    LANDING__PAGE->window.draw(LANDING__PAGE->openNewButton->rect);
    LANDING__PAGE->window.display();
}

// - - - - - - - - - - - - -

void update(LandingPage *LANDING__PAGE)
{
    LANDING__PAGE->mousePosition = sf::Mouse::getPosition(LANDING__PAGE->window);
    isButtonHovered(LANDING__PAGE->openExistingButton, LANDING__PAGE);
    isButtonHovered(LANDING__PAGE->openNewButton, LANDING__PAGE);
    isButtonPressed(LANDING__PAGE->openExistingButton, LANDING__PAGE);
    isButtonPressed(LANDING__PAGE->openNewButton, LANDING__PAGE);
    handleEvents(LANDING__PAGE);
    render(LANDING__PAGE);
}

// - - - - - - - - - - - - -

void handleEvents(LandingPage *LANDING__PAGE)
{
    sf::Event event;
    while (LANDING__PAGE->window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            LANDING__PAGE->window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            handleButtonPress(LANDING__PAGE->openExistingButton, LANDING__PAGE);
            handleButtonPress(LANDING__PAGE->openNewButton, LANDING__PAGE);
        }
    }
}

// - - - - - - - - - - - - -
int main()
{
    LandingPage landingPage;
    printf("Creating window\n");
    landingPage.window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Landing Page", sf::Style::Close);
    printf("Creating buttons\n");
    landingPage.openExistingButton = createButton(100, 200, R"(/home/somebody/Documents/RISC-y-Business/src/gui/assets/textures/landingPage/open.png)");
    landingPage.openNewButton = createButton(100, 400, R"(/home/somebody/Documents/RISC-y-Business/src/gui/assets/textures/landingPage/new.png)");
    printf("Entering main loop\n");
    while (landingPage.window.isOpen())
    {
        handleEvents(&landingPage);
        update(&landingPage);
    }

    return 0;
    //To compile: g++ landingPage.cpp -o landingPage -lsfml-graphics -lsfml-window -lsfml-system
}

// - - - - - - - - - - - -
