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
			_chessBoard[i][j].setPosition((j * 100 * scaleFactorY) + 100, (i * 100 * scaleFactorY) + _padding);
		}
}

void EventHandler::handleMouseEvents(const sf::Event& m_event)
{
	_event = m_event;
	mouseEventFlag = true;

	int originRow;
	int originCol;



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
					mouseOffset.x = mouse_pos.x - (*shared_spritesVec)[i][j].getPosition().x;
					mouseOffset.y = mouse_pos.y - (*shared_spritesVec)[i][j].getPosition().y;
					currentPiece = &(*shared_spritesVec)[i][j];

					break;
				}
			}
			if (dragging) break;
		}
	}
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
	if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left)
	{
		dragging = false;
		if (currentPiece != nullptr)
		{
			float minDistance = std::numeric_limits<float>::max();
			int closestRow = -1;
			int closestCol = -1;

			// Prolazimo kroz sva polja i tražimo najbliže.
			for (int i = 0; i < _fieldData.size(); i++)
			{
				for (int j = 0; j < _fieldData[i].size(); j++)
				{
					float distance = std::sqrt(
						std::pow(currentPiece->getPosition().x - _fieldData[i][j].fieldPosition.x, 2) +
						std::pow(currentPiece->getPosition().y - _fieldData[i][j].fieldPosition.y, 2)
					);

					if ((distance < minDistance) && _fieldData[i][j].pieceID == -1)
					{
						minDistance = distance;
						closestRow = i;
						closestCol = j;
					}
				}
			}

			
			if (closestRow != -1 && closestCol != -1 )
			{
				currentPiece->setPosition(_fieldData[closestRow][closestCol].fieldPosition);
							
			}
		}
	}

}



