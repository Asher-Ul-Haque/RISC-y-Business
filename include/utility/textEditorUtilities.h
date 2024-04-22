#ifndef TEXTEDITORUTILITIES_H
#define TEXTEDITORUTILITIES_H
#include <vector>
#include <string>
#include <stack>
#include <cmath>
#include <SFML/Graphics.hpp>

class TextEditorUtilities
{
	std::string filePath;
	std::vector<sf::Text> textContent;
	std::vector<sf::Text> lineNumbers;
	std::string textureDirectoryPath = "../include/resources/textures/";
    std::string fontDirectoryPath = "../include/resources/fonts/";
    std::string soundDirectoryPath = "../include/resources/sounds/";
	sf::RenderWindow* window;
	sf::Font font;
	sf::RectangleShape cursor;
	unsigned char cursorLine = 0;
    unsigned char cursorPos = 0;	
    unsigned char size = 24;
    unsigned char linePadding = 2;
    int bottomDisplayedLine;
    int topDisplayedLine;
    bool isEdited = false;

    sf::Clock scrollClock;
    float movementSpeed = 1.5f;
    sf::Vector2f movement;
    
	unsigned char previousCursorLine = 0;
	bool specialKeyPressed = false;
	sf::Clock keyClock;
	sf::Keyboard::Key lastKeyPress;
	
	sf::Clock colorClock;
	sf::Color textColor;
	float pi = 3.1415926f;
	float elapsedTime = 0.0f;
	float zoom = 1.0f;

	std::string status;

	typedef struct 
	{
		unsigned char cursorLine;
		unsigned char cursorPos;
		sf::Text theText[5];
	} Snapshot;

	std::stack<Snapshot> undoStack;
	std::stack<Snapshot> redoStack;
	Snapshot latest;

	sf::View scroller;	
	unsigned short viewHeight = 500;
	unsigned short viewWidth = 800;
	unsigned short minY = 0.f;
	unsigned short maxY = minY + (20 - 1) * (5 + linePadding);

	void setSpecialKeyPress();

	void updateSnapshot();
	
	void insertChar(char C);
	
	void deleteChar();
	
	void scrollUp();
	
	void scrollDown();

	void scrollLeft();

	void scrollRight();
	
	void moveCursorRight();
	
	void moveCursorLeft();
	
	void moveCursorDown();
	
	void moveCursorUp();

	void setCursorPosition();

	void addACharacter(char C);

	void makeANewLine();

	void scrollDownLogic();

	void resize();


public:
	TextEditorUtilities(){};

	TextEditorUtilities(sf::RenderWindow* WINDOW, unsigned short WIDTH, unsigned short HEIGHT);

	void setFilePath(std::string& PATH);
		
	void writeToFile();
	
	void readFromFile();
	
	void update(const sf::Event* EVENT);
	
	void render();
	
	void undo();

	void redo();	

	std::string getStatus();
};

#endif //TEXTEDITORUTILITIES_H
