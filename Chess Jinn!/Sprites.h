#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>

/// <summary>
/// sprites creation!
/// </summary>


struct Sprites
{
	sf::Texture texChessPieces;

	sf::Sprite whitePawn;
	sf::Sprite whiteRook;
	sf::Sprite whiteKnight;
	sf::Sprite whiteBishop;
	sf::Sprite whiteQueen;
	sf::Sprite whiteKing;

	sf::Sprite blackPawn;
	sf::Sprite blackRook;
	sf::Sprite blackKnight;
	sf::Sprite blackBishop;
	sf::Sprite blackQueen;
	sf::Sprite blackKing;



	Sprites();
	void loadTexturesFromDisk();
	void makeSprites(const sf::Texture& texture);

};

