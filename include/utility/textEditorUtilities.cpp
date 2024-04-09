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
	
	window->setView(scroller);
}


void TextEditorUtilities::scrollUp()
{
	viewArea = viewArea - sf::Vector2f(0, size);
}

void TextEditorUtilities::scrollDown()
{
	viewArea = viewArea - sf::Vector2f(0, size);
}

void TextEditorUtilities::setCursorPosition()
{
	cursor.setPosition(textContent[cursorLine].getPosition().x + (5 * cursorPos) + 7, cursorLine * 7 + textContent[0].getPosition().y);
}

void TextEditorUtilities::render()
{
	for (int i = 0; i < textContent.size(); ++i)
	{
		window->draw(textContent[i]);
	}
	window->draw(cursor);
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
}
	
void TextEditorUtilities::writeToFile()
{
	std::ofstream outputFile(filePath);
	switch (outputFile.is_open())
	{
		case true:
			break;
					
		case false:
			std::cerr << "Could not open file for writing" << std::endl;
			break;
	}
				
	for (const auto& lineText : textContent)
	{
		outputFile << lineText.getString().toAnsiString() << "\n";
	}
			
	outputFile.close();
	isEdited = false;
	switch(isEdited)
	{
		case false:
			return;
			break;

		case true:
			break;
	}
	
}	

void TextEditorUtilities::moveCursorDown()
{
	if (cursorLine > 0)
	{
		--cursorLine;
		setCursorPosition();
		return;
	}
}

void TextEditorUtilities::moveCursorUp()
{
	if (cursorLine < textContent.size() - 1)
	{
		++cursorLine;
		setCursorPosition();
		return;
	}
}


void TextEditorUtilities::moveCursorLeft()
{
	if (cursorPos > 0)
	{
		--cursorPos;
		setCursorPosition();
		return;
	}
	moveCursorUp();
}

void TextEditorUtilities::moveCursorRight()
{
	if (cursorPos < textContent[cursorLine].getString().toAnsiString().length() - 1)
	{
		++cursorPos;
		setCursorPosition();
		return;
	}
	moveCursorDown();
}

void TextEditorUtilities::makeANewLine()
{
	sf::Text newLine;
	newLine.setFont(font);
	newLine.setCharacterSize(size);
	newLine.setFillColor(sf::Color::Black);
	textContent.insert(textContent.begin() + cursorLine + 1, newLine);
	++cursorLine;
	cursorPos = 0;
}

void TextEditorUtilities::addACharacter(char C)
{
	sf::Text& line = textContent[cursorLine];
	std::string lineText = line.getString().toAnsiString();
	lineText.insert(cursorPos, 1, C);
	line.setString(lineText);
	++cursorPos;
}

void TextEditorUtilities::insertChar(char C)
{
	switch(C == '\n')
	{
		case true:
			makeANewLine();
			break;
			
		case false:
			addACharacter(C);
			break;
	}
	
	isEdited = true;
}

void TextEditorUtilities::deleteChar()
{
	sf::Text& line = textContent[cursorLine];
	std::string lineText = line.getString().toAnsiString();
	switch(cursorPos > 0)
	{
		case true:
			lineText.erase(cursorPos -1, 1);
			line.setString(lineText);
			--cursorPos;
			isEdited = true;
			break;
			
		case false:
			switch(cursorLine > 0)
			{
				case false:
					break;
					
				case true:
					std::string previousLine = textContent[cursorLine -1].getString().toAnsiString();
					previousLine += lineText;
					textContent.erase(textContent.begin() + cursorLine);
					--cursorLine;
					cursorPos = previousLine.length();
					isEdited = true;
					break;
			}
			break;
	}
}

void TextEditorUtilities::scrollDownLogic()
{
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
}

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
				
				case sf::Keyboard::Down:
					moveCursorDown();
					scrollDownLogic();
					break;
				
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
					
			}
			break;
			
		default:
			break;
	}
}