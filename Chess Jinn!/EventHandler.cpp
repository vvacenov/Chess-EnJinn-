#include "EventHandler.h"

bool EventHandler::isWindowClosed() 
{
	if (_event.type == sf::Event::Closed)
	{
		windowCloseFlag = true;
	}

	return windowCloseFlag;
}

void EventHandler::windowClose()
{
	_renderWindow.close();
}

void EventHandler::handleWindowEvents()
{

}