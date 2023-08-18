#include "Sprites.h"


Sprites::Sprites()
{
	loadTexturesFromDisk();
}

void Sprites::makeSprites(const sf::Texture& texture)
{
	sf::IntRect whitePawnRect(940, 0, 188, 188);
	whitePawn.setTexture(texture);
	whitePawn.setTextureRect(whitePawnRect);


	sf::IntRect whiteRookRect(752, 0, 188, 188);
	whiteRook.setTexture(texture);
	whiteRook.setTextureRect(whiteRookRect);


	sf::IntRect whiteKnightRect(564, 0, 188, 188);
	whiteKnight.setTexture(texture);
	whiteKnight.setTextureRect(whiteKnightRect);


	sf::IntRect whiteBishopRect(376, 0, 188, 188);
	whiteBishop.setTexture(texture);
	whiteBishop.setTextureRect(whiteBishopRect);


	sf::IntRect whiteQueenRect(188, 0, 188, 188);
	whiteQueen.setTexture(texture);
	whiteQueen.setTextureRect(whiteQueenRect);


	sf::IntRect whiteKingRect(0, 0, 188, 188);
	whiteKing.setTexture(texture);
	whiteKing.setTextureRect(whiteKingRect);

	/////////////////////////////////////////////////////////////////

	sf::IntRect blackPawnRect(940, 188, 188, 188);
	blackPawn.setTexture(texture);
	blackPawn.setTextureRect(blackPawnRect);


	sf::IntRect blackRookRect(752, 188, 188, 188);
	blackRook.setTexture(texture);
	blackRook.setTextureRect(blackRookRect);


	sf::IntRect blackKnightRect(564, 188, 188, 188);
	blackKnight.setTexture(texture);
	blackKnight.setTextureRect(blackKnightRect);


	sf::IntRect blackBishopRect(376, 188, 188, 188);
	blackBishop.setTexture(texture);
	blackBishop.setTextureRect(blackBishopRect);


	sf::IntRect blackQueenRect(188, 188, 188, 188);
	blackQueen.setTexture(texture);
	blackQueen.setTextureRect(blackQueenRect);


	sf::IntRect blackKingRect(0, 188, 188, 188);
	blackKing.setTexture(texture);
	blackKing.setTextureRect(blackKingRect);


}

void Sprites::loadTexturesFromDisk()
{

	if (texChessPieces.loadFromFile("textures/Chess_Pieces_Sprite.png"))
	{
		std::cout << "Texture loaded!" << std::endl;
		texChessPieces.setSmooth(true);
		makeSprites(texChessPieces);
	}

	else
	{
		std::cout << "Texture not found!" << std::endl;;
	}

}



