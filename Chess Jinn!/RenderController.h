#pragma once
#include "ChessBoard.h"
#include "EventHandler.h"
#include "Sprites.h"
#include "FieldData.h"
#include <vector>
#include <map>
#include <memory>

//define field data structure



//define piece ID's
enum class Pieces
{	
	whitePawn = 1, whiteRook, whiteKnight, whiteBishop,	whiteQueen,	whiteKing,
	blackPawn = 11, blackRook, blackKnight, blackBishop, blackQueen, blackKing
};



//main class
class RenderController
{
public:

	RenderController();
	void renderLoop();

private:
	// render
	sf::RenderWindow renderWindow;

	//chessboard
	ChessBoard chessboardField;
	Sprites sprite;
	FieldData fd;
	sf::Event event;


	std::vector <std::vector<sf::RectangleShape>> chessBoard;
	std::vector <std::vector<FieldData>> fieldData;
	std::shared_ptr<std::vector<std::vector<sf::Sprite>>>  spritesVec;


	
	unsigned int initialWindowWidth;
	unsigned int initialWindowHeight;

	//sizes
	const unsigned int fieldHeight = 100;
	const unsigned int fieldWidth = 100;
	unsigned int originalScale = fieldHeight;
	unsigned int padding = 20;
	float spritesScale = 0.53;

	//initializations
	void initBoard();
	void generateFieldData();

	//setup window
	void setupWindow();
	

	//render window loop
	void renderBoard();
	void renderSprites();

	

	//render pieces
	void createSpritesVec();
	sf::Sprite UpdateSprite(sf::Sprite& sprite, int i, int j, float scaleFactor);
		
};

