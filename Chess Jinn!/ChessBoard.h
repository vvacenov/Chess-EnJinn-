#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>


class ChessBoard
{
public:

	sf::RectangleShape getField(int id);
	ChessBoard();

private:

	sf::RectangleShape whiteField;
	sf::RectangleShape blackField;

	float fieldHeight;
	float fieldWidth;

	int blackColor[3];
	int whiteColor[3];

	void initVariables();
	void initFields();
};


