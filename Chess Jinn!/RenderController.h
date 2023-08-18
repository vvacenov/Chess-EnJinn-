#pragma once
#include "ChessBoard.h"
#include "EventHandler.h"
#include "Sprites.h"
#include <vector>
#include <map>

//define field data structure
struct FieldData
{
	int fieldID = -1;
	int pieceID = -1;
	sf::Vector2f fieldPosition = sf::Vector2f(0.f, 0.f);
	sf::Vector2f fieldScale = sf::Vector2f(1.f, 1.f);
};



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
	
private:
	// render
	sf::RenderWindow renderWindow;

	//chessboard
	ChessBoard chessboardField;
	Sprites sprite;
	FieldData fd;


	std::vector <std::vector<sf::RectangleShape>> chessBoard;
	std::vector <std::vector<FieldData>> fieldData;
	

	unsigned int initialWindowWidth;
	unsigned int initialWindowHeight;
	//sizes
	int fieldHeight;
	int fieldWidth;

	int padding = 20;

	//initializations
	void initBoard();
	void initFieldData();

	//setup window
	void setupWindow();
	

	//render window loop
	void renderBoard();
	void renderLoop();

	//render pieces
	void initSprites();

	void gameLoop();
	
};

