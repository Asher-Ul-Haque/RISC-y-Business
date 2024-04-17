#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Smooth Scrolling Example");

    sf::View view(sf::FloatRect(0, 0, 800, 600));
    window.setView(view);

    std::vector<sf::Text> texts;
    sf::Font font;
    if (!font.loadFromFile("../../include/resources/fonts/JetBrainsMono-Bold.ttf")) {
        // Error loading font
        return -1;
    }

    // Create some sample text elements
    for (int i = 0; i < 10; ++i) {
        sf::Text text("Text " + std::to_string(i), font, 24);
        text.setPosition(100.f + i * 200.f, 300.f);
        texts.push_back(text);
    }

    sf::Clock clock;
    sf::Time deltaTime;

    float movementSpeed = 100.0f; // Adjust as needed
    sf::Vector2f movement(0.0f, 0.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calculate delta time
        deltaTime = clock.restart();

        // Handle smooth movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            // Check if view left is to the right of the leftmost text element
            if (view.getCenter().x - view.getSize().x / 2 > texts.front().getPosition().x) {
                movement.x -= movementSpeed * deltaTime.asSeconds();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            // Check if view right is to the left of the rightmost text element
            if (view.getCenter().x + view.getSize().x / 2 < texts.back().getPosition().x + texts.back().getGlobalBounds().width) {
                movement.x += movementSpeed * deltaTime.asSeconds();
            }
        }

        // Update view position smoothly
        view.move(movement);
        window.setView(view);

        // Rendering
        window.clear(sf::Color::White);
        for (const auto& text : texts) {
            window.draw(text);
        }
        window.display();
    }

    return 0;
}
