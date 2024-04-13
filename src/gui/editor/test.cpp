#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Scrolling View Example");

    // Create a view for the content (everything below the top bar)
    sf::View contentView(sf::FloatRect(0, 50, 800, 550)); // Exclude top bar area
    window.setView(contentView);

    // Create your top bar (assuming it's a rectangle shape)
    sf::RectangleShape topBar(sf::Vector2f(800, 50)); // Adjust width and height as needed
    topBar.setFillColor(sf::Color::Blue);
    topBar.setPosition(0, 0); // Position above the view

    // Additional shapes for scrolling
    sf::RectangleShape rect(sf::Vector2f(50, 50));
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(100, 100);

    sf::CircleShape circle(25);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(300, 200);

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle view movement/scrolling (example: move view right)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            contentView.move(1.0f, 1.0f); // Move the content view
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            contentView.move(-1.0f, -1.0f);
        }

        window.clear();

        // Draw content
        window.setView(contentView);
  
        // Draw your content here (e.g., background, sprites, etc.)
        window.draw(rect);
        window.draw(circle);
        window.setView(window.getDefaultView()); // Reset view to window coordinates
        window.draw(topBar);

        window.display();
    }

    return 0;
}
