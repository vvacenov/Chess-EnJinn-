#pragma once
#include <SFML/Graphics.hpp>

struct FieldData
{
	int fieldID = -1;
	int pieceID = -1;
	sf::Vector2f fieldPosition = sf::Vector2f(0.f, 0.f);
	sf::Vector2f fieldScale = sf::Vector2f(1.f, 1.f);
};

