#pragma once

#include "pch.hpp"
#include "fen.hpp"

namespace ch
{
	struct Distance
	{
	public:
		int orthTo8, orthTo1, orthToH, orthToA,
			diagToA8, diagToA1, diagToH8, diagToH1;

		Distance()
		{
			orthTo8 = orthTo1 = orthToH = orthToA =
				diagToA8 = diagToA1 = diagToH8 = diagToH1 = 0;
		}
		~Distance() {}
	};
	extern std::array<Distance, BOARDSIZE> distanceArrays;

	std::array<Distance, BOARDSIZE> genDistances();

	// legal
	struct pieceLogic
	{
	public:
		bool isPieceWhite(int heldPiece);
		int getModulus(int arrayIndex, int targetIndex);
		int getRank(int arrayIndex);
		int getHeldPiece(int arrayIndex);

		bool isSlidingPiece(int heldPiece);
		bool isSlidePsuedoLegal(int arrayModulus, int heldPiece);
		bool slideUnobstructed(int arrayIndex, int arrayDelta, int arrayModulus, const std::array<int, 64>& renderBoard);
		bool slideLooped(int arrayIndex, int targetIndex);

		bool knightPsuedoLegal(int arrayIndex, int arrayDelta);

		bool pawnPsuedoLegal(int heldPiece, int arrayIndex, int arrayDelta);
		bool isWhitePawnCapture(int arrayIndex, int targetIndex);
		bool isBlackPawnCapture(int arrayIndex, int targetIndex);

		bool kingPsuedoLegal(int arrayIndex, int arrayDelta);
		bool castleUnobstructed(int targetIndex);
		bool castleAttacked(int targetIndex);
		bool castlePsuedoLegal(int arrayIndex, int targetIndex);

		bool movePsuedoLegal(int arrayIndex, int targetIndex, const std::array<int, 64>& board);
		bool trialLegal(int arrayIndex, int targetIndex);

		bool inCheck(std::array<bool, BOARDSIZE>& whiteAttackBoard, std::array<bool, BOARDSIZE>& blackAttackBoard);

		std::string isPromotion();

		bool isSquareFriendly(int targetIndex, int heldPiece);

		bool whiteMated();
		bool blackMated();

		bool blackCanMove(const std::array<int, 64>& board);
		bool whiteCanMove(const std::array<int, 64>& board);

		bool isDraw();
	public:
		bool moveLegal(int arrayIndex, int targetIndex);
	};
	extern pieceLogic PieceLogic;

	// get iter num for bitboard
	int slideToEdge(int arrayIndex, int delta);
}
