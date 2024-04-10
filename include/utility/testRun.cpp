#include "textEditorUtilities.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Text Editor Test");
    window.setFramerateLimit(60); // Limit to 60 FPS

    TextEditorUtilities textEditor(&window); // Create text editor
    std::string file = "textfile.txt";
    textEditor.setFilePath(file);
    textEditor.readFromFile();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            } 
            textEditor.update(&event);
        }

        window.clear(sf::Color::White);
        textEditor.render(); // Render the text editor
        window.display();
    }

    return 0;
}
