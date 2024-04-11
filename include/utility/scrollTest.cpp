#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML View Scrolling");
    sf::View view(sf::FloatRect(0, 0, 800, 600)); // Initial view

    // Create shapes for demonstration
    sf::RectangleShape rect1(sf::Vector2f(100, 50));
    rect1.setFillColor(sf::Color::Red);
    rect1.setPosition(100, 100);

    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition(300, 200);

    sf::RectangleShape rect2(sf::Vector2f(150, 75));
    rect2.setFillColor(sf::Color::Green);
    rect2.setPosition(500, 350);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle key presses for scrolling
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        view.move(-10.f, 0.f);
                        break;
                    case sf::Keyboard::Right:
                        view.move(10.f, 0.f);
                        break;
                    case sf::Keyboard::Up:
                        view.move(0.f, -10.f);
                        break;
                    case sf::Keyboard::Down:
                        view.move(0.f, 10.f);
                        break;
                    default:
                        break;
                }
            }
        }

        window.clear();

        // Apply the view to the window
        window.setView(view);

        // Draw shapes in the world coordinates
        window.draw(rect1);
        window.draw(circle);
        window.draw(rect2);

        window.display();
    }

    return 0;
}
