#include "RenderController.h"

RenderController::RenderController()
{
	initBoard();
	generateFieldData();
	spritesVec = std::make_shared<std::vector<std::vector<sf::Sprite>>>(8, std::vector<sf::Sprite>(8));
	createSpritesVec();
	setupWindow();
	renderLoop();

}

//function to draw chess board out of sf::RectangleShapes
void RenderController::initBoard()
{
	std::vector<sf::RectangleShape> row;
	row.reserve(8);
	//sizes



	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int fieldColorID = (i + j) % 2;

			sf::RectangleShape localField = chessboardField.getField(fieldColorID);
			localField.setPosition((j + 1) * fieldWidth, (i * fieldWidth) + padding);
			localField.setSize(sf::Vector2f(fieldHeight, fieldWidth));
			row.push_back(localField);
			std::cout << row[j].getPosition().y;
		}

		chessBoard.push_back(row);
		row.clear();
	}
}

//function to generate data about the each field
void RenderController::generateFieldData()
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
				case 7:
					fd.pieceID = static_cast<int>(Pieces::whiteRook);
					break;
				case 1:
				case 6:
					fd.pieceID = static_cast<int>(Pieces::whiteKnight);
					break;
				case 2:
				case 5:
					fd.pieceID = static_cast<int>(Pieces::whiteBishop);
					break;
				case 3:
					fd.pieceID = static_cast<int>(Pieces::whiteQueen);
					break;
				case 4:
					fd.pieceID = static_cast<int>(Pieces::whiteKing);
					break;
				default:
					fd.pieceID = -1;
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
				case 0:
				case 7:
					fd.pieceID = static_cast<int>(Pieces::blackRook);
					break;
				case 1:
				case 6:
					fd.pieceID = static_cast<int>(Pieces::blackKnight);
					break;
				case 2:
				case 5:
					fd.pieceID = static_cast<int>(Pieces::blackBishop);
					break;
				case 3:
					fd.pieceID = static_cast<int>(Pieces::blackQueen);
					break;
				case 4:
					fd.pieceID = static_cast<int>(Pieces::blackKing);
					break;
				default:
					fd.pieceID = -1;
					break;
				}
			}
			else
			{
				fd.pieceID = -1;
			}
			row.push_back(fd);
			std::cout << row[j].fieldID;
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

	EventHandler eventHandler(event, renderWindow, chessBoard, padding, initialWindowHeight, fieldHeight, fieldWidth, fieldData, spritesVec);

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
			{
			case sf::Event::Resized:

				generateFieldData();
				eventHandler.handleWindowEvents();
				
				eventHandler.resetResizeFlag();
				break;
			}
			renderWindow.clear();

			renderBoard();
			eventHandler.handleMouseEvents(event);

			renderSprites();
			renderWindow.display();
					
		}
	
	}
}

//prepare pieces for rendering

void RenderController::createSpritesVec()
{
	Sprites& spritesRef = sprite;


	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			renderWindow.draw(chessBoard[i][j]); // <- board
			float scaleFactor = chessBoard[i][j].getGlobalBounds().height / originalScale;
			sf::Vector2f position = chessBoard[i][j].getPosition();
			fieldData[i][j].fieldPosition = position;

			switch (fieldData[i][j].pieceID) // <- pieces
			{
			case 1:	//whitePawns draw
				(*spritesVec)[i][j] = UpdateSprite(spritesRef.whitePawn, i, j, scaleFactor);
				break;
			case 2:	//whiteRooks draw
				(*spritesVec)[i][j] = UpdateSprite(spritesRef.whiteRook, i, j, scaleFactor);
				break;
			case 3:	//whiteKnights draw
				(*spritesVec)[i][j] = UpdateSprite(spritesRef.whiteKnight, i, j, scaleFactor);
				break;
			case 4: //whiteBishops draw
				(*spritesVec)[i][j] = UpdateSprite(spritesRef.whiteBishop, i, j, scaleFactor);
				break;
			case 5: //whiteQueen draw
				(*spritesVec)[i][j] = UpdateSprite(spritesRef.whiteQueen, i, j, scaleFactor);
				break;
			case 6: //whiteKing draw
				(*spritesVec)[i][j] = UpdateSprite(spritesRef.whiteKing, i, j, scaleFactor);
				break;
			case 11:	//blackPawns draw
				(*spritesVec)[i][j] = UpdateSprite(spritesRef.blackPawn, i, j, scaleFactor);
				break;
			case 12://blackRooks draw
				(*spritesVec)[i][j] = UpdateSprite(spritesRef.blackRook, i, j, scaleFactor);
				break;
			case 13:	//blackKnights draw
				(*spritesVec)[i][j] = UpdateSprite(spritesRef.blackKnight, i, j, scaleFactor);
				break;
			case 14: //blackBishops draw
				(*spritesVec)[i][j] = UpdateSprite(spritesRef.blackBishop, i, j, scaleFactor);;
				break;
			case 15: //blackQueen draw
				(*spritesVec)[i][j] = UpdateSprite(spritesRef.blackQueen, i, j, scaleFactor);
				break;
			case 16: //blackKing draw
				(*spritesVec)[i][j] = UpdateSprite(spritesRef.blackKing, i, j, scaleFactor);
				break;
			default:
				(*spritesVec)[i][j] = sf::Sprite();
				break;
			}
		}
	}
}

sf::Sprite RenderController::UpdateSprite(sf::Sprite& sprite, int i, int j, float scaleFactor)
{
	sprite.setPosition(fieldData[i][j].fieldPosition.x, fieldData[i][j].fieldPosition.y);
	sprite.setScale((fieldData[i][j].fieldScale.x * spritesScale) * scaleFactor, (fieldData[i][j].fieldScale.y * spritesScale) * scaleFactor);
	return sprite;
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

		}
	}
}

//render pieces
void RenderController::renderSprites()
{
	for (int i = 0; i < (*spritesVec).size(); i++)
	{
		for (int j = 0; j < (*spritesVec)[i].size(); j++)
		{
			renderWindow.draw((*spritesVec)[i][j]);
		}
	}
}
