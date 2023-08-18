#include "RenderController.h"

RenderController::RenderController()
{
	initBoard();
	initFieldData();
	setupWindow();
	renderLoop();
}

//function to draw chess board out of sf::RectangleShapes
void RenderController::initBoard()
{
	std::vector<sf::RectangleShape> row;
	row.reserve(8);
	int rowOffestY = 100;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int fieldColorID = (i + j) % 2;

			sf::RectangleShape localField = chessboardField.getField(fieldColorID);
			localField.setPosition((i + 1) * 100, (j * 100) + padding);
			row.push_back(localField);
			std::cout << row[j].getPosition().y;
		}

		chessBoard.push_back(row);
		row.clear();
	}
}

//function to generate data about the each field
void RenderController::initFieldData()
{
	int fieldID_num = 0;
	std::vector<FieldData> row;
	row.reserve(8);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			fd.fieldID = fieldID_num++;
			fd.fieldPosition = chessBoard[i][j].getPosition();

			//white major pieces
			if (i == 0)
			{
				switch (j)
				{
				case 0: case 7:
					fd.pieceID = static_cast<int>(Pieces::whiteRook);
					break;
				case 1: case 6:
					fd.pieceID = static_cast<int>(Pieces::whiteKnight);
					break;
				case 2: case 5:
					fd.pieceID = static_cast<int>(Pieces::whiteBishop);
					break;
				case 3:
					fd.pieceID = static_cast<int>(Pieces::whiteQueen);
					break;
				case 4:
					fd.pieceID = static_cast<int>(Pieces::whiteKing);
					break;
				}
			}

			//white pawns
			else if (i == 1)
			{
				fd.pieceID = static_cast<int>(Pieces::whitePawn);
			}

			//black pawns
			else if (i == 6)
			{
				fd.pieceID = static_cast<int>(Pieces::blackPawn);
			}

			//black major pieces
			else if (i == 7)
			{
				switch (j)
				{
				case 0: case 7:
					fd.pieceID = static_cast<int>(Pieces::blackRook);
					break;
				case 1: case 6:
					fd.pieceID = static_cast<int>(Pieces::blackKnight);
					break;
				case 2: case 5:
					fd.pieceID = static_cast<int>(Pieces::blackBishop);
					break;
				case 3:
					fd.pieceID = static_cast<int>(Pieces::blackQueen);
					break;
				case 4:
					fd.pieceID = static_cast<int>(Pieces::blackKing);
					break;
				}
			}

			row.push_back(fd);
		}

		fieldData.push_back(row);
		row.clear();
	}
}


// create render window
void RenderController::setupWindow()
{
	unsigned int initialWindowWidth = 1200;
	unsigned int initialWindowHeight = 800 + (2 * padding);

	renderWindow.create(sf::VideoMode(initialWindowWidth, initialWindowHeight), "Chess Jinn!");
	renderWindow.setSize(sf::Vector2u(initialWindowWidth, initialWindowHeight));
}


void RenderController::renderLoop()
{
	sf::Event event;

	EventHandler eventHandler(event, renderWindow, chessBoard);

	while (renderWindow.isOpen())
	{
		//close window
		while (renderWindow.pollEvent(event))
		{
			if (eventHandler.isWindowClosed())
			{
				eventHandler.windowClose();
			}
		}
		

		renderWindow.clear();
		renderBoard();
		renderWindow.display();
	}
}

//render board
void RenderController::renderBoard()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			renderWindow.draw(chessBoard[i][j]);
		}
	}
}







