#include "textEditorUtilities.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

TextEditorUtilities::TextEditorUtilities(sf::RenderWindow* WINDOW, unsigned short WIDTH, unsigned short HEIGHT) : window(WINDOW)
{
	viewWidth = WIDTH;
	viewHeight = HEIGHT;
	font.loadFromFile(fontDirectoryPath + "JetBrainsMono-Light.ttf");
	colorClock.restart();
	
	scroller.reset(sf::FloatRect(0, 0, viewWidth, viewHeight));

	cursor.setSize(sf::Vector2f(5 * (size / 12), size));
	cursor.setFillColor(sf::Color(135, 136, 140));
	
	window->setView(scroller);
	movement = sf::Vector2f(0, 0);
}

void TextEditorUtilities::scrollUp()
{
	movement.y -= movementSpeed * scrollClock.restart().asSeconds();
	if (movement.y < -movementSpeed)
	{
		movement.y = -movementSpeed;
	}
	window->setView(scroller);
}

void TextEditorUtilities::scrollDown()
{
	movement.y += movementSpeed * scrollClock.restart().asSeconds();
	if (movement.y > movementSpeed)
	{
		movement.y = movementSpeed;
	}
	window->setView(scroller);
}

void TextEditorUtilities::scrollLeft()
{
	if (textContent[0].getPosition().x < 80)
	{
		return;
	}
	for (int i = 0; i < textContent.size(); ++i)
	{
		textContent[i].move(-movementSpeed * scrollClock.restart().asSeconds(), 0);
	}
	setCursorPosition();
}

void TextEditorUtilities::scrollRight()
{
	for (int i = 0; i < textContent.size(); ++i)
	{
		textContent[i].move(movementSpeed * scrollClock.restart().asSeconds(), 0);
	}
	setCursorPosition();
}

void TextEditorUtilities::setCursorPosition()
{
	cursor.setPosition(textContent[cursorLine].getPosition().x + (7 * cursorPos * (size / 12)), cursorLine * size + textContent[0].getPosition().y);
}

std::string TextEditorUtilities::getStatus()
{
	return status;
}

void TextEditorUtilities::render()
{
	scroller.move(movement);
	window->setView(scroller);
	lineNumbers[0].setString("1");
	elapsedTime = colorClock.getElapsedTime().asSeconds() * 2;
    float red = (std::sin(elapsedTime + 0) * 127) + 128;
    float green = (std::sin(elapsedTime + 2 * pi / 3) * 127) + 128;
    float blue = (std::sin(elapsedTime + 4 * pi / 3) * 127) + 128;
	textColor = sf::Color(red, green, blue);
	window->setView(scroller);
	window->draw(cursor);
	for (int i = 0; i < textContent.size(); ++i)
	{
		textContent[i].setFillColor(textColor);
		lineNumbers[i].setFillColor(textColor);
		window->draw(textContent[i]);
		window->draw(lineNumbers[i]);
	}
}

void TextEditorUtilities::setFilePath(std::string& PATH)
{
	filePath = PATH;
}

void TextEditorUtilities::readFromFile()
{
	status = "Reading from file" + filePath;
	std::ifstream infile(filePath);
	cursorPos = 0;
	cursorLine = 0;
	scroller.reset(sf::FloatRect(0, 0, viewWidth, viewHeight));
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
	lineNumbers.clear();
	
	std::string line;
	int i = 2;

	if (infile.peek() == std::ifstream::traits_type::eof()) 
	{
        sf::Text text;
        sf::Text number;
        text.setFont(font);
		number.setFont(font);
		text.setFillColor(sf::Color::Black);
		number.setFillColor(sf::Color::Black);
		text.setCharacterSize(size);
		number.setCharacterSize(size);
		text.setString("Enter something in your file");
		number.setString(std::to_string(1));
		text.setPosition(sf::Vector2f(80, 60));
		number.setPosition(sf::Vector2f(10, 60)); 
		textContent.push_back(text);
		lineNumbers.push_back(number);
		infile.close();
		writeToFile();
		readFromFile();
		setCursorPosition();
		return;
    }

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		sf::Text text;
		sf::Text number;
		text.setFont(font);
		number.setFont(font);
		text.setFillColor(sf::Color::Black);
		number.setFillColor(sf::Color::Black);
		text.setCharacterSize(size);
		number.setCharacterSize(size);
		text.setString(line);
		number.setString(std::to_string((int)i - 1));
		text.setPosition(sf::Vector2f(80, (i * size) + 60));
		number.setPosition(sf::Vector2f(10, (i * size) + 60));
		++i;
		
		textContent.push_back(text);
		lineNumbers.push_back(number);
	}
	setCursorPosition();	
	topDisplayedLine = 0;
	bottomDisplayedLine = std::min((int)textContent.size() - 1, 25);
	infile.close();	
}
	
void TextEditorUtilities::writeToFile()
{
	status = "writing to file path" + filePath;
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
	sf::Text newNumber;
	newLine.setFont(font);
	newNumber.setFont(font);
	newLine.setCharacterSize(size);
	newNumber.setCharacterSize(size);
	newLine.setFillColor(sf::Color::Black);
	newNumber.setFillColor(sf::Color::Black);
	textContent.insert(textContent.begin() + cursorLine + 1, newLine);
	lineNumbers.insert(lineNumbers.begin() + cursorLine + 1, newNumber);

	++cursorLine;
	std::string previousLine = textContent[cursorLine -1].getString().toAnsiString();
	std::string whatGoesBefore  = previousLine.substr(0, cursorPos);
	std::string whatGoesAfter = previousLine.substr(cursorPos);
	textContent[cursorLine - 1].setString(whatGoesBefore);
	textContent[cursorLine].setString(whatGoesAfter);
	cursorPos = 0;
	lineNumbers[cursorLine].setString(std::to_string((int) cursorLine + 1));
	for (int i = cursorLine; i < textContent.size(); ++i)
	{
		textContent[i].setPosition(sf::Vector2f(80, ((i + 2) * size) + 60));
		lineNumbers[i].setPosition(textContent[i].getPosition());
		lineNumbers[i].move(-70, 0);
		lineNumbers[i].setString(std::to_string((int) i + 1));
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
						textContent[i].setPosition(sf::Vector2f(80, ((i + 2) * size) + 60));
						lineNumbers[i].setPosition(textContent[i].getPosition());
						lineNumbers[i].move(-70, 0);
						lineNumbers[i].setString(std::to_string((int) i + 1));
					}
					isEdited = true;
					setCursorPosition();
					break;
			}
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
	switch(redoStack.empty()) 
	{
		case true:
			std::cout << "Redo stack is empty!" << std::endl;
			break;

		case false:
            latest = redoStack.top();
            redoStack.pop();

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
	status = "CursorLine:\t" + std::to_string(cursorLine) + "\t\tCursorPosition:\t" + std::to_string(cursorPos) + "\t\tTotal:\t" + std::to_string(textContent.size()) + "\n";
	for (auto i : textContent)
	{
		i.setFillColor(textColor);
	}
	
	switch(abs(previousCursorLine - cursorLine) < 5)
	{
		case true:
			break;
			
		case false:
			previousCursorLine = cursorLine;
			if (lastKeyPress == sf::Keyboard::Down || lastKeyPress == sf::Keyboard::Up || lastKeyPress == sf::Keyboard::Left || lastKeyPress == sf::Keyboard::Right || lastKeyPress == sf::Keyboard::Home || lastKeyPress == sf::Keyboard::End)
			{
				previousCursorLine = cursorLine;
				updateSnapshot();
				undoStack.push(latest);
			}
			break;
	}
	
	switch(specialKeyPressed)
	{
		case true:
			updateSnapshot();
			undoStack.push(latest);
			specialKeyPressed = false;
			break;
			
		case false:
			break;
	}
	
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
				case sf::Keyboard::Space:
					window->setView(scroller);
					break;

				case sf::Keyboard::Left:
					switch (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
					{
						case true:
							scrollLeft();
							break;

						case false:
							moveCursorLeft();
							break;
					}
					break;
					
				case sf::Keyboard::Right:
					switch (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
					{
						case true:
							scrollRight();
							break;

						case false:
							moveCursorRight();
							break;
					}
					break;
					
				case sf::Keyboard::Up:
					switch (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
					{
						case true:
							scrollUp();
							break;

						case false:
							moveCursorUp();
							break;
					}
					break;
				
				case sf::Keyboard::Down:
					switch (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
					{
						case true:
							scrollDown();				
							break;

						case false:
							moveCursorDown();
							break;
					}
					break;
					
					break;

				case sf::Keyboard::PageUp:
					switch(sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
					{
						case true:	
							movement.x = movement.y = 0;
							break;

						case false:
							break;
					}
					scrollUp();
					break;

				case sf::Keyboard::PageDown:
					scrollDown();
					break;

				case sf::Keyboard::S:
					switch(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
					{
						case true:
							writeToFile();
							break;
						
						case false:
							break;
					}
					break;

				case sf::Keyboard::Z:
					switch(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
					{
						case true:
							switch(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
							{
								case true:
									std::cout << "Redo Call detected" <<std::endl;
									redo();
									break;
									
								case false:
									std::cout << "Undo call detected" << std::endl;
									undo();
									break;
							}
							break;
					}
					break;

				case sf::Keyboard::Equal:
					{
						switch (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
						{
							case true:
								++size;
								resize();
								break;

							case false:
								break;
						}
					}
					break;

				case sf::Keyboard::Hyphen:
					{
						switch (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
						{
							case true:
								--size;
								resize();
								break;

							case false:
								break;
						}
					}
					break;


				case sf::Keyboard::Return:
					setSpecialKeyPress();
					makeANewLine();
					break;

				case sf::Keyboard::Tab:
					setSpecialKeyPress();
					for (int i = 0; i < 4; ++i)
					{
						insertChar(' ');
					}
					break;

				case sf::Keyboard::Delete:
					setSpecialKeyPress();
					cursorPos++;
					if (cursorPos >= textContent[cursorLine].getString().toAnsiString().length() && textContent.size() - 1 > cursorLine)
					{
						cursorLine++;
						cursorPos = 0;
						deleteChar();
					}
					else
					{
						deleteChar();
						--cursorPos;
					}
					
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

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& !sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)&& !sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) 
	{
       float magnitude = std::sqrt(movement.y * movement.y);
       if (magnitude > 0.1f) 
       {
           float decelerationStep = std::min(movementSpeed * scrollClock.restart().asSeconds(), movementSpeed);
           movement.y -= (movement.y / magnitude) * decelerationStep;
       } 
       else 
       {
           movement.y = 0.0f;
       }
    }
}

void TextEditorUtilities::setSpecialKeyPress()
{
	switch(keyClock.getElapsedTime().asSeconds() > 1)
	{
		case true:
			specialKeyPressed = true;
			keyClock.restart();
			break;
			
		case false:
			specialKeyPressed = false;
			break;
	}
	updateSnapshot();
	undoStack.push(latest);
}


void TextEditorUtilities::resize()
{
	cursor.setSize(sf::Vector2f(5 * (size / 12), size));
	for (int i = 0; i < textContent.size(); ++i)
	{
		textContent[i].setCharacterSize(size);
		lineNumbers[i].setCharacterSize(size);
	}
}