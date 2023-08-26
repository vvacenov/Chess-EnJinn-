#include "EventHandler.h"

bool EventHandler::isWindowClosed()
{
	if (_event.type == sf::Event::Closed)
	{
		windowCloseFlag = true;
	}
	else windowCloseFlag = false;

	return windowCloseFlag;
}

void EventHandler::windowClose()
{
	_renderWindow.close();
}

void EventHandler::handleWindowEvents()
{

	sf::FloatRect visibleArea(0, 0, _event.size.width, _event.size.height);
	_renderWindow.setView(sf::View(visibleArea));
	float scaleFactorY = (static_cast<float>(_event.size.height) - (2 * _padding)) / (_initialWindowHeight - (2 * _padding));


	for (int i = 0; i < _chessBoard.size(); i++)

		for (int j = 0; j < _chessBoard[i].size(); j++)
		{
			_chessBoard[i][j].setSize(sf::Vector2f(_fieldHeight * scaleFactorY, _fieldWidth * scaleFactorY));
			_fieldData[i][j].fieldScale = _chessBoard[i][j].getScale();
			_chessBoard[i][j].setPosition((j * 100 * scaleFactorY) + 100, (i * 100 * scaleFactorY) + _padding);
			_fieldData[i][j].fieldPosition = _chessBoard[i][j].getPosition();
		}
}

void EventHandler::handleMouseEvents(const sf::Event& m_event)
{
	_event = m_event;
	mouseEventFlag = true;
	
	eventMouseClick();
	eventMouseMove();
	eventMouseRelease();
}

void EventHandler::eventMouseClick()

{
	if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left)
	{
		auto mouse_pos = sf::Mouse::getPosition(_renderWindow);
		dragging = false;

		for (int i = 0; i < _fieldData.size(); i++)
		{
			for (int j = 0; j < _fieldData[i].size(); j++)
			{
				if ((*shared_spritesVec)[i][j].getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
				{
					dragging = true;
					updateFieldDataOnClick(i, j);
					mouseOffset.x = mouse_pos.x - (*shared_spritesVec)[i][j].getPosition().x;
					mouseOffset.y = mouse_pos.y - (*shared_spritesVec)[i][j].getPosition().y;
					currentPiece = &(*shared_spritesVec)[i][j];

					break;
				}
			}
			if (dragging) break;
		}
	}
}


void EventHandler::eventMouseMove()
{
	if (_event.type == sf::Event::MouseMoved && dragging)
	{
		auto mouse_pos = sf::Mouse::getPosition(_renderWindow);
		if (currentPiece != nullptr)
		{
			currentPiece->setPosition(mouse_pos.x - mouseOffset.x, mouse_pos.y - mouseOffset.y);
		}
		else
		{
			std::cout << "currentPiece je nullptr";
		}
	}
}

void EventHandler::eventMouseRelease()
{

	if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left)
	{
		dragging = false;
		if (currentPiece != nullptr)
		{
			float minDistance = std::numeric_limits<float>::max();
			int closestRow = -1;
			int closestCol = -1;


			for (int i = 0; i < _fieldData.size(); i++)
			{
				for (int j = 0; j < _fieldData[i].size(); j++)
				{


					float distance = std::sqrt(std::pow(currentPiece->getPosition().x - _fieldData[i][j].fieldPosition.x, 2)
						+ std::pow(currentPiece->getPosition().y - _fieldData[i][j].fieldPosition.y, 2));

					if ((distance < minDistance) && _fieldData[i][j].pieceID == -1)
					{
						minDistance = distance;
						closestRow = i;
						closestCol = j;
						updateFieldDataOnRelease(i, j);						
					}
				}
			}

			if (closestRow != -1 && closestCol != -1)
				if (_fieldData[closestRow][closestCol].pieceID == -1)  // Provjerite je li ploèa prazna
				{
					currentPiece->setPosition(_fieldData[closestRow][closestCol].fieldPosition);
				}
				else
				{
					
				}

		}
	}
}

void EventHandler::updateFieldDataOnClick(int i, int j)
{
	
	originalPieceID = _fieldData[i][j].pieceID;
	_fieldData[i][j].pieceID = -1;

}

void EventHandler::updateFieldDataOnRelease(int closestRow, int closestCol)
{
	_fieldData[closestRow][closestCol].pieceID = originalPieceID;
	originalPieceID = -1;
}
