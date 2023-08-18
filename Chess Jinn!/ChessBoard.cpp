#include "ChessBoard.h"


ChessBoard::ChessBoard()
{
	initVariables();
	initFields();
}

void ChessBoard::initVariables()
{	
	//sizes
	fieldHeight = 100;
	fieldWidth = 100;

	//colors
	whiteColor[0] = 240;
	whiteColor[1] = 215;
	whiteColor[2] = 180;

	blackColor[0] = 180;
	blackColor[1] = 135;
	blackColor[2] = 100;
}

void ChessBoard::initFields()
{
	whiteField.setSize(sf::Vector2f(fieldHeight, fieldWidth));
	whiteField.setFillColor(sf::Color(whiteColor[0], whiteColor[1], whiteColor[2]));

	blackField.setSize(sf::Vector2f(fieldHeight, fieldWidth));
	blackField.setFillColor(sf::Color(blackColor[0], blackColor[1], blackColor[2]));
}

sf::RectangleShape ChessBoard::getField(int id)
{
	if (id == 1)
	{
		return whiteField;
	}
	else if (id == 0)
	{
		return blackField;
	}
	else
	{
		std::cout << "Field id missing.";
	}
}
