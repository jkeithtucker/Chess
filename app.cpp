#include "pch.hpp"
#include "window.hpp"
#include "fen.hpp"
#include "bitboards.hpp"
#include "chess.hpp"


void debugBoard(std::array<int, 64> board)
{
	for (int i = 0; i < 64; i++)
	{
		if (i % 8 == 0)
			std::cout << "\n";
		if (board[i] >= 0)
			std::cout << " ";

		std::cout << board[i] << " ";
	}
	std::cout << "\n";
}

void debugBitboard(std::array<bool, 64> board)
{
	for (int i = 0; i < 64; i++)
	{
		if (i % 8 == 0)
			std::cout << "\n";
		if (board[i] >= 0)
			std::cout << " ";

		std::cout << board[i] << " ";
	}
	std::cout << "\n";
}

int app()
{
	SpriteStruct* sprites = loadSprites();

	sf::RenderWindow* window = createWin();
	window->setVerticalSyncEnabled(true);

	// bitboard generation
	bb::generateAttackBoards(trueFEN.FENBoard, bb::whiteAttacks, bb::blackAttacks);

	// game loop
	while (window->isOpen())
	{
		window->clear();

		drawBoard(window);

		drawPieces(window, sprites, trueFEN.FENBoard);

		window->display();

		// event handling
		sf::Event event;
		while (window->pollEvent(event))
		{
			// piece movement
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				movePiece(window, sprites);

				// game end conditions
				if (ch::PieceLogic.blackMated())
					printf("BLACK MATED\n");
				if (ch::PieceLogic.whiteMated())
					printf("WHITE MATED\n");
				if (ch::PieceLogic.isDraw())
					printf("DRAW\n");
			}

			// close window & exit loop
			if (event.type == sf::Event::Closed)
				window->close();
		}
	}
	return 0;
}