#include <SFML/Graphics.hpp>
#include <iostream>

class TextBox {
public:
    TextBox(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, sf::Font& font) 
        : window(window), position(position), size(size), font(font) {
        textBox.setSize(size);
        textBox.setPosition(position);
        textBox.setFillColor(sf::Color::White);
        textBox.setOutlineThickness(2);
        textBox.setOutlineColor(sf::Color::Black);

        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(position.x + 5, position.y + 5);

        cursor.setSize(sf::Vector2f(2, 20));
        cursor.setFillColor(sf::Color::Black);
        cursor.setPosition(text.getPosition().x + text.getLocalBounds().width + 5, position.y + 5);
    }

    void handleInput(sf::Event& event) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode >= 32 && event.text.unicode <= 126) { // ASCII printable characters
                input += static_cast<char>(event.text.unicode);
                text.setString(input);
                updateCursorPosition();
            }
            else if (event.text.unicode == 8 && input.size() > 0) { // Backspace
                input.pop_back();
                text.setString(input);
                updateCursorPosition();
            }
        }
    }

    void updateCursorPosition() {
        sf::FloatRect textBounds = text.getLocalBounds();
        cursor.setPosition(text.getPosition().x + textBounds.width + 5, cursor.getPosition().y);
    }

    void draw() {
        window.draw(textBox);
        window.draw(text);
        if (showCursor) {
            window.draw(cursor);
        }
    }

private:
    sf::RenderWindow& window;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::RectangleShape textBox;
    sf::Text text;
    sf::RectangleShape cursor;
    std::string input;
    bool showCursor = true;
    sf::Font& font;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML TextBox Example");
    sf::Font font;
    if (!font.loadFromFile("../../include/resources/fonts/JetBrainsMono-Bold.ttf")) {
        std::cerr << "Failed to load font\n";
        return 1;
    }

    TextBox textBox(window, sf::Vector2f(100, 100), sf::Vector2f(300, 40), font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            textBox.handleInput(event);
        }

        window.clear(sf::Color::White);
        textBox.draw();
        window.display();
    }

    return 0;
}
