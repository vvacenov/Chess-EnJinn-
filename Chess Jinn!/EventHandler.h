#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <SFML/graphics.hpp>
#include "FieldData.h"



class EventHandler
{
public:
		
	bool isWindowResized() const { return windowEventFlag; }
	bool isMousePressed() const { return mouseEventFlag; }
	bool isWindowClosed();

	void resetResizeFlag() { windowEventFlag = false; }
	void resetMouseFlag() { mouseEventFlag = false; }

	void handleWindowEvents();
	void handleMouseEvents(const sf::Event& m_event);
	void windowClose();

	
	EventHandler(sf::Event& event, sf::RenderWindow& renderWindow, std::vector<std::vector<sf::RectangleShape>>& chessBoard, int padding, unsigned int initialWindowHeight, int fieldHeight, int fieldWidth, std::vector <std::vector<FieldData>>& fieldData, std::shared_ptr<std::vector<std::vector<sf::Sprite>>> sprites)
		: 
		_event(event), 
		_renderWindow(renderWindow), 
		_chessBoard(chessBoard),
		_padding(padding),
		_initialWindowHeight(initialWindowHeight),
		_fieldHeight(fieldHeight),
		_fieldWidth(fieldWidth),
		_fieldData(fieldData),
		shared_spritesVec(sprites)


	{};

private:	

	sf::Event& _event;
	sf::RenderWindow& _renderWindow;
	std::vector<std::vector<sf::RectangleShape>>& _chessBoard;
	std::vector<std::vector<FieldData>>& _fieldData;
	std::shared_ptr<std::vector<std::vector<sf::Sprite>>> shared_spritesVec;
	sf::Sprite* currentPiece = nullptr;
	sf::Vector2f originalPosition;
	sf::Vector2f mouseOffset;

	bool windowEventFlag = false;
	bool mouseEventFlag = false;
	bool windowCloseFlag = false;
	bool dragging = false;

	int _padding;
	int originalPieceID = -1;
	unsigned int _initialWindowHeight;
	float _fieldHeight;
	float _fieldWidth;

	void eventMouseClick();
	void eventMouseMove();
	void eventMouseRelease();
	void updateFieldDataOnClick(int i, int j);
	void updateFieldDataOnRelease(int closestRow, int closestCol);

};

