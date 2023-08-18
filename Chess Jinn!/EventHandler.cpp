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