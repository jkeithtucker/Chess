#include "pch.hpp"
#include "window.hpp"
#include "chess.hpp"
#include "fen.hpp"
#include "bitboards.hpp"

// declarations
sf::RectangleShape brdSqr;
sf::Color PromColor(200, 0, 0, 200);

SpriteStruct* loadSprites(void)
{
	// allocate textures on heap
	sf::Texture* wPawn = new sf::Texture;
	sf::Texture* wKnight = new sf::Texture;
	sf::Texture* wBishop = new sf::Texture;
	sf::Texture* wRook = new sf::Texture;
	sf::Texture* wQueen = new sf::Texture;
	sf::Texture* wKing = new sf::Texture;

	sf::Texture* bPawn = new sf::Texture;
	sf::Texture* bKnight = new sf::Texture;
	sf::Texture* bBishop = new sf::Texture;
	sf::Texture* bRook = new sf::Texture;
	sf::Texture* bQueen = new sf::Texture;
	sf::Texture* bKing = new sf::Texture;

	// load png for texture
	wPawn->loadFromFile("../../../assets/wPawn.png");
	wKnight->loadFromFile("../../../assets/wKnight.png");
	wBishop->loadFromFile("../../../assets/wBishop.png");
	wRook->loadFromFile("../../../assets/wRook.png");
	wQueen->loadFromFile("../../../assets/wQueen.png");
	wKing->loadFromFile("../../../assets/wKing.png");

	bPawn->loadFromFile("../../../assets/bPawn.png");
	bKnight->loadFromFile("../../../assets/bKnight.png");
	bBishop->loadFromFile("../../../assets/bBishop.png");
	bRook->loadFromFile("../../../assets/bRook.png");
	bQueen->loadFromFile("../../../assets/bQueen.png");
	bKing->loadFromFile("../../../assets/bKing.png");

	// allocate sprites on heap
	sf::Sprite* wP = new sf::Sprite;
	sf::Sprite* wN = new sf::Sprite;
	sf::Sprite* wB = new sf::Sprite;
	sf::Sprite* wR = new sf::Sprite;
	sf::Sprite* wQ = new sf::Sprite;
	sf::Sprite* wK = new sf::Sprite;

	sf::Sprite* bP = new sf::Sprite;
	sf::Sprite* bN = new sf::Sprite;
	sf::Sprite* bB = new sf::Sprite;
	sf::Sprite* bR = new sf::Sprite;
	sf::Sprite* bQ = new sf::Sprite;
	sf::Sprite* bK = new sf::Sprite;

	// map textures onto sprites
	wP->setTexture(*wPawn);
	wN->setTexture(*wKnight);
	wB->setTexture(*wBishop);
	wR->setTexture(*wRook);
	wQ->setTexture(*wQueen);
	wK->setTexture(*wKing);

	bP->setTexture(*bPawn);
	bN->setTexture(*bKnight);
	bB->setTexture(*bBishop);
	bR->setTexture(*bRook);
	bQ->setTexture(*bQueen);
	bK->setTexture(*bKing);

	// filling struct for return
	SpriteStruct* sprites = new SpriteStruct;

	sprites->whitePawn = wP;
	sprites->whiteKnight = wN;
	sprites->whiteBishop = wB;
	sprites->whiteRook = wR;
	sprites->whiteQueen = wQ;
	sprites->whiteKing = wK;

	sprites->blackPawn = bP;
	sprites->blackKnight = bN;
	sprites->blackBishop = bB;
	sprites->blackRook = bR;
	sprites->blackQueen = bQ;
	sprites->blackKing = bK;

	return sprites;
}

sf::RenderWindow* createWin(void)
{
	// window construction
	sf::RenderWindow* window = new sf::RenderWindow;
	window->create(sf::VideoMode(winRes.x, winRes.y), "Chess", sf::Style::Close);
	window->setPosition(sf::Vector2i(0, 0));

	return window;
}

void drawBoard(sf::RenderWindow* window)
{
	int xPos, yPos;
	bool colourFlip = true;
	brdSqr.setSize(sf::Vector2f(sqrSize, sqrSize));

	// draw board (White orientation)
	xPos = yPos = boardOffset;
	for (int i = 0; i < BOARDSIZE; i++)
	{
		if (i % 8 == 0 && i != 0)
		{
			yPos += sqrSize;
			xPos = boardOffset;
			colourFlip = !colourFlip;
		}

		if ((i + colourFlip) % 2 == 0)
			brdSqr.setFillColor(Brown);
		else
			brdSqr.setFillColor(sf::Color::White);

		brdSqr.setPosition(xPos, yPos);
		window->draw(brdSqr);
		xPos += sqrSize;
	}
}

void drawPieces(sf::RenderWindow* window, const SpriteStruct* sprites, std::array<int, BOARDSIZE> board)
{
	int xPos, yPos;
	xPos = yPos = boardOffset;

	std::array<int, 64> renderBoard = board;

	for (int i = 0; i < BOARDSIZE; i++)
	{
		if (i % 8 == 0 && i != 0) // next rank of board
		{
			yPos += sqrSize;
			xPos = boardOffset;
		}

		switch (renderBoard[i])
		{
		case 0: // empty square
			break;

		case P: // White pieces
			sprites->whitePawn->setPosition(xPos, yPos);
			window->draw(*sprites->whitePawn);
			break;
		case N:
			sprites->whiteKnight->setPosition(xPos, yPos);
			window->draw(*sprites->whiteKnight);
			break;
		case B:
			sprites->whiteBishop->setPosition(xPos, yPos);
			window->draw(*sprites->whiteBishop);
			break;
		case R:
			sprites->whiteRook->setPosition(xPos, yPos);
			window->draw(*sprites->whiteRook);
			break;
		case Q:
			sprites->whiteQueen->setPosition(xPos, yPos);
			window->draw(*sprites->whiteQueen);
			break;
		case K:
			sprites->whiteKing->setPosition(xPos, yPos);
			window->draw(*sprites->whiteKing);
			break;

		case p: // White pieces
			sprites->blackPawn->setPosition(xPos, yPos);
			window->draw(*sprites->blackPawn);
			break;
		case n:
			sprites->blackKnight->setPosition(xPos, yPos);
			window->draw(*sprites->blackKnight);
			break;
		case b:
			sprites->blackBishop->setPosition(xPos, yPos);
			window->draw(*sprites->blackBishop);
			break;
		case r:
			sprites->blackRook->setPosition(xPos, yPos);
			window->draw(*sprites->blackRook);
			break;
		case q:
			sprites->blackQueen->setPosition(xPos, yPos);
			window->draw(*sprites->blackQueen);
			break;
		case k:
			sprites->blackKing->setPosition(xPos, yPos);
			window->draw(*sprites->blackKing);
			break;
		}
		xPos += sqrSize;
	}
}

bool isCursorInBoard(int cursorX, int cursorY)
{
	if (cursorX < boardOffset || cursorX > boardEnd
		|| cursorY < boardOffset || cursorY > boardEnd)
		return false;
	else
		return true;
}

sf::Sprite getDragPiece(int heldPiece, const SpriteStruct* sprites)
{
	sf::Sprite workSprite;
	switch (heldPiece)
	{
	case P:
		workSprite.setTexture(*sprites->whitePawn->getTexture());
		break;

	case N:
		workSprite.setTexture(*sprites->whiteKnight->getTexture());
		break;

	case B:
		workSprite.setTexture(*sprites->whiteBishop->getTexture());
		break;

	case R:
		workSprite.setTexture(*sprites->whiteRook->getTexture());
		break;

	case Q:
		workSprite.setTexture(*sprites->whiteQueen->getTexture());
		break;

	case K:
		workSprite.setTexture(*sprites->whiteKing->getTexture());
		break;

	case p:
		workSprite.setTexture(*sprites->blackPawn->getTexture());
		break;

	case n:
		workSprite.setTexture(*sprites->blackKnight->getTexture());
		break;

	case b:
		workSprite.setTexture(*sprites->blackBishop->getTexture());
		break;

	case r:
		workSprite.setTexture(*sprites->blackRook->getTexture());
		break;

	case q:
		workSprite.setTexture(*sprites->blackQueen->getTexture());
		break;

	case k:
		workSprite.setTexture(*sprites->blackKing->getTexture());
		break;

	default:
		break;
	}
	return workSprite;
}

void drawSpriteOnCursor(sf::RenderWindow* window, sf::Sprite workSprite)
{
	sf::Vector2i dragPos = sf::Mouse::getPosition(*window);
	workSprite.setPosition(dragPos.x - (sqrSize / 2), dragPos.y - (sqrSize / 2));
	window->draw(workSprite);
}

void dragPiece(sf::RenderWindow* window, const SpriteStruct* sprites, int heldPiece, std::array<int, BOARDSIZE> renderBoard)
{
	sf::Sprite dragDraw = getDragPiece(heldPiece, sprites);

	window->clear();

	drawBoard(window);

	drawPieces(window, sprites, renderBoard);

	drawSpriteOnCursor(window, dragDraw);

	window->display();
}

int getArrayIndex(int cursorX, int cursorY)
{
	cursorX -= boardOffset; // setting pixPos to the begining of the board
	cursorY -= boardOffset;
	int arrInd = floor(cursorX / sqrSize) + (floor(cursorY / sqrSize) * 8);
	return arrInd;
}

void movePiece(sf::RenderWindow* window, const SpriteStruct* sprites)
{
	int heldPiece, arrayIndex, targetIndex;
	bool isDragging = false;

	std::array<int, 64> renderBoard = trueFEN.FENBoard;

	// piece movement
	sf::Vector2i firstPos = sf::Mouse::getPosition(*window);
	if (!isCursorInBoard(firstPos.x, firstPos.y))
		return; // mouse pressed outside of board
	else
	{
		arrayIndex = getArrayIndex(firstPos.x, firstPos.y);
		heldPiece = renderBoard[arrayIndex];
		isDragging = true;
	}

	// remove drag piece from render board
	renderBoard[arrayIndex] = 0;

	while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		dragPiece(window, sprites, heldPiece, renderBoard);

	sf::Vector2i newPos = sf::Mouse::getPosition(*window);
	if (!isCursorInBoard(newPos.x, newPos.y)) {
		heldPiece = 0;
	}
	else if (heldPiece != 0)
	{
		targetIndex = getArrayIndex(newPos.x, newPos.y);
		if (ch::PieceLogic.moveLegal(arrayIndex, targetIndex))
		{
			trueFEN.FENBoard[arrayIndex] = 0;
			trueFEN.FENBoard[targetIndex] = heldPiece;

			if (ch::PieceLogic.isPromotion() != "false")
			{
				drawPromotion(window, sprites, targetIndex);
				promotionChoice(window, targetIndex);
			}
		}
		else
			;
	}
}

void drawPromotion(sf::RenderWindow* window, const SpriteStruct* sprites, int index)
{
	if (ch::PieceLogic.isPromotion() == "white")
	{
		int i, promY;
		int promX = (index * sqrSize) + boardOffset;

		for (i = 0, promY = 0; i < 4; ++i, promY += sqrSize)
		{
			brdSqr.setPosition(promX, promY + boardOffset);
			brdSqr.setFillColor(PromColor);
			window->draw(brdSqr);
		}

		promY = boardOffset;
		sprites->whiteQueen->setPosition(promX, promY);
		window->draw(*sprites->whiteQueen);
		sprites->whiteRook->setPosition(promX, promY + (sqrSize));
		window->draw(*sprites->whiteRook);
		sprites->whiteBishop->setPosition(promX, promY + (sqrSize * 2));
		window->draw(*sprites->whiteBishop);
		sprites->whiteKnight->setPosition(promX, promY + (sqrSize * 3));
		window->draw(*sprites->whiteKnight);
	}
	else if (ch::PieceLogic.isPromotion() == "black")
	{
		int i, promX, promY;

		promX = ((index - 56) * sqrSize) + boardOffset;
		promY = boardEnd - sqrSize;

		for (i = 0; i < 4; ++i, promY -= sqrSize)
		{
			brdSqr.setPosition(promX, promY);
			brdSqr.setFillColor(PromColor);
			window->draw(brdSqr);
		}

		promY = boardEnd - sqrSize;
		sprites->blackQueen->setPosition(promX, promY);
		window->draw(*sprites->blackQueen);
		sprites->blackRook->setPosition(promX, promY - (sqrSize));
		window->draw(*sprites->blackRook);
		sprites->blackBishop->setPosition(promX, promY - (sqrSize * 2));
		window->draw(*sprites->blackBishop);
		sprites->blackKnight->setPosition(promX, promY - (sqrSize * 3));
		window->draw(*sprites->blackKnight);
	}
	window->display();
}

void promotionChoice(sf::RenderWindow* window, int targetIndex)
{
	while (true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && ch::PieceLogic.isPromotion() == "white")
		{
			sf::Vector2i newPos = sf::Mouse::getPosition(*window);
			newPos.x -= boardOffset;
			newPos.y -= boardOffset;
			int chosenIndex = floor(newPos.x / sqrSize) + (floor(newPos.y / sqrSize) * 8);

			switch (chosenIndex - targetIndex)
			{
			case 0:
				trueFEN.FENBoard[targetIndex] = Q;
				return;
			case 8:
				trueFEN.FENBoard[targetIndex] = R;
				return;
			case 16:
				trueFEN.FENBoard[targetIndex] = B;
				return;
			case 24:
				trueFEN.FENBoard[targetIndex] = N;
				return;
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && ch::PieceLogic.isPromotion() == "black")
		{
			sf::Vector2i newPos = sf::Mouse::getPosition(*window);
			newPos.x -= boardOffset;
			newPos.y -= boardOffset;
			int chosenIndex = floor(newPos.x / sqrSize) + (floor(newPos.y / sqrSize) * 8);

			switch (chosenIndex - targetIndex)
			{
			case 0:
				trueFEN.FENBoard[targetIndex] = q;
				return;
			case -8:
				trueFEN.FENBoard[targetIndex] = r;
				return;
			case -16:
				trueFEN.FENBoard[targetIndex] = b;
				return;
			case -24:
				trueFEN.FENBoard[targetIndex] = n;
				return;
			}
		}
	}
}