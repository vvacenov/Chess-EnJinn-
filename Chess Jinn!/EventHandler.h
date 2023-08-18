#pragma once
#include <vector>
#include <SFML/graphics.hpp>

class EventHandler
{
public:
		
	bool isWindowResized() const { return windowEventFlag; }
	bool isMousePressed() const { return mouseEventFlag; }
	bool isWindowClosed();

	void resetResizeFlag() { windowEventFlag = false; }
	void resetMouseFlag() { mouseEventFlag = false; }

	void handleWindowEvents();
	void handleMouseEvents();
	void windowClose();

	EventHandler(sf::Event& event, sf::RenderWindow& renderWindow, std::vector<std::vector<sf::RectangleShape>>& chessBoard) 
		: 
		_event(event), 
		_renderWindow(renderWindow), 
		_chessBoard(chessBoard) 
	{};

private:	

	sf::Event& _event;
	sf::RenderWindow& _renderWindow;
	std::vector<std::vector<sf::RectangleShape>>& _chessBoard;

	bool windowEventFlag = false;
	bool mouseEventFlag = false;
	bool windowCloseFlag = false;


	
};

