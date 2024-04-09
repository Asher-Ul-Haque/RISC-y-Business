#include "textEditorUtilities.h"
#include <fstream>
#include <sstream>
#include <iostream>

TextEditorUtilities::TextEditorUtilities(sf::RenderWindow* WINDOW) : window(WINDOW)
{
	font.loadFromFile(fontDirectoryPath + "JetBrainsMono-Light.ttf");
	
	scroller.setSize(viewArea);
	scroller.setCenter(viewArea / 2.f);
	
	cursor.setSize(sf::Vector2f(2, size));
	cursor.setFillColor(sf::Color::Black);
	cursor.setOrigin(sf::Vector2f(1, 6));
	
	window->setView(scroller);
	clock.restart();
}

/*
void TextEditorUtitilies::scrollUp()
{
	scroller.move(0, -size);
}

void TextEditorUtitilies::scrollDown()
{
	scroller.move(0, size);
}
*/
void TextEditorUtilities::render()
{
	for (int i = 0; i < textContent.size(); ++i)
	{
		window->draw(textContent[i]);
	}
	if (showCursor)
	{
		window->draw(cursor);
	}
}

void TextEditorUtilities::setFilePath(std::string& PATH)
{
	filePath = PATH;
}

void TextEditorUtilities::readFromFile()
{
	std::ifstream infile(filePath);
	switch (infile.is_open())
	{
		case true:
			break;
			
		case false:
			std::cerr << "Error opening file to read\n";
			return;
			break;
	}
	
	textContent.clear();
	
	std::string line;
	int i = 2;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		sf::Text text;
		text.setFont(font);
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(size);
		text.setString(line);
		text.setPosition(sf::Vector2f(40, i*size));
		++i;
		
		textContent.push_back(text);
	}
	
	infile.close();	
	cursor.setPosition(sf::Vector2f(cursorLine + 30, cursorPos + 30));

}
/*	
void writeToFile()
{
	switch(isEdited)
	{
		case false:
			return;
			break;
	}
	
	std::ofstream outputFile(filePath);
	switch (outputFile.is_open())
	{
		case true:
			break;
			
		case false:
			std::cerr << "Could not open file for writing" << std::endl;
			return;
			break;
	}
	
	for (const auto& lineText : textContent)
	{
		outputFile << text.getString().toAnsiString() << "\n";
	}
	
	outputFile.close();
	isEdited = false;
}	
	
void TextEditorUtitilies::moveCursorDown()
{
	if (cursorLine > 0)
	{
		--cursorLine;
		return;
	}
}

void TextEditorUtitilies::moveCursorUp()
{
	if (cursorLine < textContent.size() - 1)
	{
		++cursorLine;
		return;
	}
}

void TextEditorUtitilies::moveCursorLeft()
{
	if (cursorPos > 0)
	{
		--cursorPos;
		return;
	}
	moveCursorUp();
}

void TextEditorUtitilies::moveCursorRight()
{
	if (cursorPos < textContent[cursorLine].size() - 1)
	{
		++cursorPos;
		return;
	}
	moveCursorDown();
}

void TextEditorUtitilies::insertChar(char C)
{
	switch(C == '\n')
	{
		case true:
			sf::Text newLine;
			newLine.setFont(font);
			newLine.setCharacterSize(size);
			newLine.setFillColor(sf::Color::Black);
			textContent.insert(textContent.begin() + cursorline + 1, newLine);
			++cursorLine;
			cursorPos = 0;
			break;
			
		case false:
			std::Text& line = textContent[cursorLine];
			std::string& lineText = line.getSring();
			lineText.insert(cursorPos, 1, C);
			line.setString(lineText);
			++cursorPos;
			break;
	}
	
	isEdited = true;
}

void TextEditorUtitilies::deleteChar()
{
	sf::Text& line = textContent[cursorLine];
	std::string& lineText = line.getString();
	switch(cursorPos > 0)
	{
		case true:
			lineText.erase(cursorPos -1, 1);
			currentLine.setString(lineText);
			--cursorPos;
			isEdited = true;
			break;
			
		case false:
			switch(cursor.line > 0)
			{
				case false:
					break;
					
				case true:
					std::string& previousLine = textContent[cursorLine -1].getString();
					previousLine += lineText;
					textContent.erase(textContent.begin() + cursorLine);
					--cursorLine;
					cursorPos = previousLine.length();
					isEdited = true;
					BREAK;
			}
			break;
	}
}
*/

void TextEditorUtilities::update(const sf::Event* EVENT)
{
	switch(EVENT->type)
	{
		case sf::Event::TextEntered:
			switch(EVENT->text.unicode >= 32 && EVENT->text.unicode <127 || EVENT->text.unicode == '\n')
			{
				case true:
					insertChar(static_cast<char>(EVENT->text.unicode));				
					break;
					
				case false:
					switch(EVENT->text.unicode == '\b')
					{
						case true:
							deleteChar();
							break;
							
						case false:
							break;
					}
					break;
			}
			break;
			
		case sf::Event::KeyPressed:
			switch(EVENT->key.code)
			{
				case sf::Keyboard::Left:
					moveCursorLeft();
					break;
					
				case sf::Keyboard::Right:
					moveCursorRight();
					break;
					
				case sf::Keyboard::Up:
					moveCursorUp();
					switch(viewArea.y > 0.f)
					{
						case true:
							scrollUp();
							break;
							
						case false:
							break;
					}
					break;
				/*	
				case sf::Keyboard::Down:
					moveCursorDown();
					float totalLinesHeight = textContent.size() * (textContent[0].getGlobalBounds().height + linePadding);
					float windowHeight = window->getSize().y;
					switch(totalLinesHeight - viewArea.y > window->getSize().y)
					{
						case true:
							scrollDown();
							break;
							
						case false:
							break;
					}
					break;
				/*	
				case sf::Keyboard::S:
					switch(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
					{
						case true:
							writeToFile();
							break;
						
						case false:
							break;
					}
					break;
					*/
			}
			break;
			
		default:
			break;
	}
}