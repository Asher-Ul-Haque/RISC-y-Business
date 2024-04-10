#include "textEditorUtilities.h"
#include <fstream>
#include <sstream>
#include <iostream>

TextEditorUtilities::TextEditorUtilities(sf::RenderWindow* WINDOW) : window(WINDOW)
{
	font.loadFromFile(fontDirectoryPath + "JetBrainsMono-Light.ttf");
	
	scroller.setSize(viewArea);
	scroller.setCenter(viewArea / 2.f);
	
	cursor.setSize(sf::Vector2f(5, size));
	cursor.setFillColor(sf::Color(100, 0, 0, 100));
	
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
	cursor.setPosition(textContent[cursorLine].getPosition().x + (7 * cursorPos), cursorLine * 12 + textContent[0].getPosition().y);
}

void TextEditorUtilities::render()
{
	window->draw(cursor);
	for (int i = 0; i < textContent.size(); ++i)
	{
		window->draw(textContent[i]);
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
	if (infile.peek() == std::ifstream::traits_type::eof()) 
	{
        infile.close();
        return;  // Return if the file is empty
    }
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
	setCursorPosition();	
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

void TextEditorUtilities::moveCursorUp()
{
	if (cursorLine > 0)
	{
		--cursorLine;
		cursorPos = (cursorPos > textContent[cursorLine].getString().toAnsiString().length()) ? textContent[cursorLine].getString().toAnsiString().length() : cursorPos;
		setCursorPosition();
		return;
	}
}

void TextEditorUtilities::moveCursorDown()
{
	if (cursorLine < textContent.size() - 1)
	{
		++cursorLine;
		cursorPos = (cursorPos > textContent[cursorLine].getString().toAnsiString().length()) ? textContent[cursorLine].getString().toAnsiString().length() : cursorPos;
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
	if (cursorLine > 0)
	{
		cursorPos = textContent[cursorLine - 1].getString().toAnsiString().length();
	}
	moveCursorUp();
}

void TextEditorUtilities::moveCursorRight()
{
	if (cursorPos < textContent[cursorLine].getString().toAnsiString().length())
	{
		++cursorPos;
		setCursorPosition();
		return;
	}
	if (cursorLine < textContent.size() -1)
	{
		cursorPos = 0;
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
	std::string previousLine = textContent[cursorLine -1].getString().toAnsiString();
	std::string whatGoesBefore  = previousLine.substr(0, cursorPos);
	std::string whatGoesAfter = previousLine.substr(cursorPos);
	textContent[cursorLine - 1].setString(whatGoesBefore);
	textContent[cursorLine].setString(whatGoesAfter);
	cursorPos = 0;
	for (int i = cursorLine; i < textContent.size(); ++i)
	{
		textContent[i].setPosition(sf::Vector2f(40, (i + 2) * size));
	}
	
	isEdited = true;

	setCursorPosition();
}

void TextEditorUtilities::addACharacter(char C)
{
	sf::Text& line = textContent[cursorLine];
	std::string lineText = line.getString().toAnsiString();
	lineText.insert(cursorPos, 1, C);
	line.setString(lineText);
	++cursorPos;
	setCursorPosition();
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
			setCursorPosition();
			break;
			
		case false:
			switch(cursorLine > 0)
			{
				case false:
					break;
					
				case true:
					std::string previousLine = textContent[cursorLine -1].getString().toAnsiString();
					cursorPos = previousLine.length();
					previousLine += lineText;
					textContent.erase(textContent.begin() + cursorLine);
					textContent[cursorLine - 1].setString(previousLine);
					--cursorLine;
					for (int i = cursorLine; i < textContent.size(); ++i)
					{
						textContent[i].setPosition(sf::Vector2f(40, (i + 2) * size));
					}
					isEdited = true;
					setCursorPosition();
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

void TextEditorUtilities::undo()
{
	switch(undoStack.empty()) 
	{
		case true:
			std::cout << "Undo stack is empty!" << std::endl;
			break;

		case false:
            redoStack.push(latest);
            latest = undoStack.top();
            undoStack.pop();

            cursorLine = latest.cursorLine;
            cursorPos = latest.cursorPos;

            int startLine = cursorLine > 2 ? cursorLine - 2 : 0;
            int endLine = cursorLine + 2 < textContent.size() ? cursorLine + 2 : textContent.size() - 1;
            for (int i = startLine; i <= endLine; ++i) 
			{
                textContent[i] = latest.theText[i - startLine];
            }

    }
}

void TextEditorUtilities::redo()
{
	
}

void TextEditorUtilities::updateSnapshot()
{
	Snapshot newSnap;
    newSnap.cursorLine = cursorLine;
    newSnap.cursorPos = cursorPos;

    int startLine = cursorLine > 2 ? cursorLine - 2 : 0;
    int endLine = cursorLine + 2 < textContent.size() ? cursorLine + 2 : textContent.size() - 1;
    for (int i = startLine; i <= endLine; ++i) 
	{
		newSnap.theText[i - startLine] = textContent[i];
    }

    latest = newSnap;
}

void TextEditorUtilities::update(const sf::Event* EVENT)
{
	switch(EVENT->type)
	{
		case sf::Event::TextEntered:
			switch(EVENT->text.unicode >= 32 && EVENT->text.unicode <127)
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

				case sf::Keyboard::PageUp:
					updateSnapshot();
					undoStack.push(latest);
					std::cout << "Push to undo stack complete" << std::endl;
					break;

				case sf::Keyboard::S:
					switch(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					{
						case true:
							writeToFile();
							break;
						
						case false:
							break;
					}
					break;

				case sf::Keyboard::Z:
					switch(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
					{
						case true:
							std::cout << "Undo call detected" << std::endl;
							undo();
							break;

						case false:
							break;
							redo();
					}
					break;
					
				case sf::Keyboard::Return:
					makeANewLine();
					break;

				case sf::Keyboard::Tab:
					for (int i = 0; i < 4; ++i)
					{
						insertChar(' ');
					}
					break;

				case sf::Keyboard::Delete:
					cursorPos++;
					if (cursorPos >= textContent[cursorLine].getString().toAnsiString().length() && textContent.size() - 1 > cursorLine)
					{
						cursorLine++;
						cursorPos = 0;
					}
					deleteChar();
					break;

				case sf::Keyboard::Home:
					cursorPos = 0;
					setCursorPosition();
					break;

				case sf::Keyboard::End:
					cursorPos = textContent[cursorLine].getString().toAnsiString().length();
					setCursorPosition();
					break;
			}
			break;
			
		default:
			break;
	}
}