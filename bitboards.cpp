#include "pch.hpp"
#include "bitboards.hpp"
#include "chess.hpp"
#include "app.hpp"

namespace bb
{
	// bitboard declaration
	std::array<bool, BOARDSIZE> whiteAttacks, trialWhiteAttacks;
	std::array<bool, BOARDSIZE> blackAttacks, trialBlackAttacks;
	std::array<bool, BOARDSIZE> occupiedSquares;

	// funcs
	void generateAttackBoards(const std::array<int, BOARDSIZE>& board, std::array<bool, BOARDSIZE>& whiteAttackBoard, std::array<bool, BOARDSIZE>& blackAttackBoard)
	{
		clearAttackBoards(whiteAttackBoard, blackAttackBoard);

		for (int i = 0; i < BOARDSIZE; i++)
		{
			if (board[i] == 0)
				continue;
			if (board[i] > 0)
			{
				generateWhiteAttackBoard(i, board, whiteAttackBoard);
			}
			if (board[i] < 0)
			{
				generateBlackAttackBoard(i, board, blackAttackBoard);
			}
		}

	}

	bool isOutOfRange(int x)
	{
		if (x >= BOARDSIZE || x < 0)
			return true;
		else
			return false;
	}

	void whitePawnAttacks(const int arrayIndex, std::array<bool, BOARDSIZE>& attackBoard)
	{
		for (auto attack : WHITEPAWNATTACK)
		{
			if (isOutOfRange(arrayIndex + attack))
				continue;
			else if (!ch::PieceLogic.slideLooped(arrayIndex, arrayIndex + attack))
				attackBoard[arrayIndex + attack] = true;
		}
	}

	void blackPawnAttacks(const int arrayIndex, std::array<bool, BOARDSIZE>& attackBoard)
	{
		for (auto attack : BLACKPAWNATTACK)
		{
			if (isOutOfRange(arrayIndex + attack))
				continue;
			else if (!ch::PieceLogic.slideLooped(arrayIndex, arrayIndex + attack))
				attackBoard[arrayIndex + attack] = true;
		}
	}

	void knightAttacks(const int arrayIndex, std::array<bool, BOARDSIZE>& attackBoard, const std::array<int, 64>& board)
	{
		for (auto move : KNIGHTMOVES)
		{
			if (isOutOfRange(arrayIndex + move))
				continue;
			else if (ch::PieceLogic.movePsuedoLegal(arrayIndex, arrayIndex + move, board))
				attackBoard[arrayIndex + move] = true;
		}
	}

	void bishopAttacks(const int arrayIndex, std::array<bool, BOARDSIZE>& attackBoard, const std::array<int, 64>& board)
	{
		for (auto move : BISHOPMOVES)
		{
			int iternum = ch::slideToEdge(arrayIndex, move);
			for (int i = 1; i <= iternum; i++)
			{
				if (isOutOfRange(arrayIndex + move * i))
					break;
				else if (ch::PieceLogic.movePsuedoLegal(arrayIndex, arrayIndex + move * i, board))
					attackBoard[arrayIndex + move * i] = true;
			}
		}
	}

	void rookAttacks(const int arrayIndex, std::array<bool, BOARDSIZE>& attackBoard, const std::array<int, 64>& board)
	{
		for (auto move : ROOKMOVES)
		{
			int iternum = ch::slideToEdge(arrayIndex, move);
			for (int i = 1; i <= iternum; i++)
			{
				if (isOutOfRange(arrayIndex + move * i))
					break;
				else if (ch::PieceLogic.movePsuedoLegal(arrayIndex, arrayIndex + move * i, board))
					attackBoard[arrayIndex + move * i] = true;
			}
		}
	}

	void queenAttacks(const int arrayIndex, std::array<bool, BOARDSIZE>& attackBoard, const std::array<int, 64>& board)
	{
		for (auto move : QUEENMOVES)
		{
			int iternum = ch::slideToEdge(arrayIndex, move);
			for (int i = 1; i <= iternum; i++)
			{
				if (isOutOfRange(arrayIndex + move * i))
					break;
				else if (ch::PieceLogic.movePsuedoLegal(arrayIndex, arrayIndex + move * i, board))
					attackBoard[arrayIndex + move * i] = true;
			}
		}
	}

	void kingAttacks(const int arrayIndex, std::array<bool, BOARDSIZE>& attackBoard, const std::array<int, 64>& board)
	{
		for (auto move : KINGMOVES)
		{
			if (isOutOfRange(arrayIndex + move))
				continue;
			else if (ch::PieceLogic.movePsuedoLegal(arrayIndex, arrayIndex + move, board))
				attackBoard[arrayIndex + move] = true;
		}
	}

	void clearAttackBoards(std::array<bool, BOARDSIZE>& whiteAttackBoard, std::array<bool, BOARDSIZE>& blackAttackBoard)
	{
		for (int i = 0; i < BOARDSIZE; i++)
		{
			whiteAttackBoard[i] = false;
			blackAttackBoard[i] = false;
		}
	}

	void generateWhiteAttackBoard(const int arrayIndex, const std::array<int, BOARDSIZE>& board, std::array<bool, BOARDSIZE>& whiteAttackBoard)
	{
		switch (board[arrayIndex])
		{
		case P:
			whitePawnAttacks(arrayIndex, whiteAttackBoard);
			break;
		case N:
			knightAttacks(arrayIndex, whiteAttackBoard, board);
			break;
		case B:
			bishopAttacks(arrayIndex, whiteAttackBoard, board);
			break;
		case R:
			rookAttacks(arrayIndex, whiteAttackBoard, board);
			break;
		case Q:
			queenAttacks(arrayIndex, whiteAttackBoard, board);
			break;
		case K:
			kingAttacks(arrayIndex, whiteAttackBoard, board);
			break;
		}
	}

	void generateBlackAttackBoard(const int arrayIndex, const std::array<int, BOARDSIZE>& board, std::array<bool, BOARDSIZE>& blackAttackBoard)
	{
		switch (board[arrayIndex])
		{
		case p:
			blackPawnAttacks(arrayIndex, blackAttackBoard);
			break;
		case n:
			knightAttacks(arrayIndex, blackAttackBoard, board);
			break;
		case b:
			bishopAttacks(arrayIndex, blackAttackBoard, board);
			break;
		case r:
			rookAttacks(arrayIndex, blackAttackBoard, board);
			break;
		case q:
			queenAttacks(arrayIndex, blackAttackBoard, board);
			break;
		case k:
			kingAttacks(arrayIndex, blackAttackBoard, board);
			break;
		}
	}

	void generateOccupiedSquares()
	{
		for (int i = 0; i < BOARDSIZE; i++)
		{
			switch (trueFEN.FENBoard[i])
			{
			case 0:
				occupiedSquares[i] = false;
				break;
			default:
				occupiedSquares[i] = true;
				break;
			}
		}
	}
}