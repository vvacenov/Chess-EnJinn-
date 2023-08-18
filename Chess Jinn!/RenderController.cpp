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
	//sizes
	fieldHeight = 100;
	fieldWidth = 100;

	int rowOffestY = 100;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int fieldColorID = (i + j) % 2;

			sf::RectangleShape localField = chessboardField.getField(fieldColorID);
			localField.setPosition((i + 1) * 100, (j * 100) + padding);
			localField.setSize(sf::Vector2f(fieldHeight, fieldWidth));
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
				case 0: 
					fd.pieceID = static_cast<int>(Pieces::whiteRook);
					break;
				case 1: 
					fd.pieceID = static_cast<int>(Pieces::whiteKnight);
					break;
				case 2: 
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
				case 7:
					fd.pieceID = static_cast<int>(Pieces::blackRook);
					break;
				case 6:
					fd.pieceID = static_cast<int>(Pieces::blackKnight);
					break;
				case 5:
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
	initialWindowWidth = 1200;
	initialWindowHeight = 800 + (2 * padding);

	renderWindow.create(sf::VideoMode(initialWindowWidth, initialWindowHeight), "Chess Jinn!");
	renderWindow.setSize(sf::Vector2u(initialWindowWidth, initialWindowHeight));
}


void RenderController::renderLoop()
{
	sf::Event event;

	EventHandler eventHandler(event, renderWindow, chessBoard, padding, initialWindowHeight, fieldHeight, fieldWidth);

	while (renderWindow.isOpen())
	{
		//close window
		while (renderWindow.pollEvent(event))
		{
			if (eventHandler.isWindowClosed())
			{
				eventHandler.windowClose();
			}

			switch (event.type)

			case sf::Event::Resized:
			{
				eventHandler.handleWindowEvents();
				eventHandler.resetResizeFlag();
				break;
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
	Sprites& spritesRef = sprite;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			renderWindow.draw(chessBoard[i][j]);
			
			if (fieldData[i][j].pieceID == 1)
			{
				spritesRef.whitePawn.setPosition(fieldData[i][j].fieldPosition.x, fieldData[i][j].fieldPosition.y);
				spritesRef.whitePawn.setScale(0.53, 0.53);
				renderWindow.draw(spritesRef.whitePawn);
			}
		}
	}
}


//render pieces

void RenderController::initSprites()
{



}




