#include "pch.hpp"
#include "chess.hpp"
#include "bitboards.hpp"
#include "app.hpp"

namespace ch
{
	// piece logic struct
	bool pieceLogic::isPieceWhite(int heldPiece)
	{
		if (heldPiece > 0)
			return true;
		else
			return false;
	}

	int pieceLogic::getModulus(int arrayIndex, int targetIndex)
	{
		int arrayModulus = 0;
		int arrayDelta = targetIndex - arrayIndex;
		int arrayRank = floor(arrayIndex / 8) * 8;

		if (arrayDelta % 7 == 0)
			arrayModulus = 7;
		if (arrayDelta % 9 == 0)
			arrayModulus = 9;

		if (arrayDelta % 8 == 0)
			arrayModulus = 8;
		if (targetIndex >= arrayRank && targetIndex <= arrayRank + 7)
			arrayModulus = 1;

		return arrayModulus;
	}

	int pieceLogic::getRank(int arrayIndex)
	{
		int arrayRank = floor(arrayIndex / 8);
		arrayRank = arrayRank * -1 + 8;

		return arrayRank;
	}

	int pieceLogic::getHeldPiece(int arrayIndex)
	{
		return trueFEN.FENBoard[arrayIndex];
	}

	bool pieceLogic::isSlidingPiece(int heldPiece)
	{
		switch (heldPiece)
		{
		case B:
			return true;
		case R:
			return true;
		case Q:
			return true;

		case b:
			return true;
		case r:
			return true;
		case q:
			return true;

		default:
			return false;
		}
	}

	bool pieceLogic::isSlidePsuedoLegal(int arrayModulus, int heldPiece)
	{
		if (arrayModulus == 0)
			return false;

		if (heldPiece == Q || heldPiece == q)
			return true;

		if ((heldPiece == R || heldPiece == r) && (arrayModulus == 8 || arrayModulus == 1))
			return true;

		if ((heldPiece == B || heldPiece == b) && (arrayModulus == 9 || arrayModulus == 7))
			return true;

		return false;
	}

	bool pieceLogic::slideUnobstructed(int arrayIndex, int arrayDelta, int arrayModulus, const std::array<int, 64>& workBoard)
	{	// slideUnobstructed() looks at squares upto, not including, the target
		// kings do not obstruct slides, as they cannot be obstructive
		int i, j;
		int iterationNum = arrayDelta / arrayModulus - 1;
		if (iterationNum < 0)
		{
			iterationNum *= -1;
			arrayModulus *= -1;
			iterationNum -= 2;
		}

		for (i = arrayIndex + arrayModulus, j = 0; j < iterationNum; j++, i += arrayModulus)
		{
			if (j > 0 && slideLooped(i, i + arrayModulus))
				return false;
			if (isPieceWhite(workBoard[arrayIndex]) && workBoard[i] == k)
				continue;
			if (!isPieceWhite(workBoard[arrayIndex]) && workBoard[i] == K)
				continue;
			if (workBoard[i] != 0)
				return false;
		}
		return true;
	}

	bool pieceLogic::slideLooped(int arrayIndex, int targetIndex)
	{
		if ((arrayIndex + 1) % 8 == 0 && targetIndex % 8 == 0)
			return true;
		if (arrayIndex % 8 == 0 && (targetIndex + 1) % 8 == 0)
			return true;
		return false;
	}

	bool pieceLogic::knightPsuedoLegal(int arrayIndex, int arrayDelta)
	{
		if ((arrayIndex - 1) % 8 == 0)
			if (arrayDelta == 6 || arrayDelta == -10)
				return false;
		if (arrayIndex % 8 == 0)
			if (arrayDelta == 6 || arrayDelta == -10 || arrayDelta == 15 || arrayDelta == -17)
				return false;
		if ((arrayIndex + 1) % 8 == 0)
			if (arrayDelta == -6 || arrayDelta == 10 || arrayDelta == -15 || arrayDelta == 17)
				return false;
		if ((arrayIndex + 2) % 8 == 0)
			if (arrayDelta == -6 || arrayDelta == 10)
				return false;

		if (arrayDelta < 0)
			arrayDelta *= -1;

		if (arrayDelta == 6 || arrayDelta == 10 || arrayDelta == 15 || arrayDelta == 17)
			return true;
		else
			return false;
	}

	bool pieceLogic::pawnPsuedoLegal(int heldPiece, int arrayIndex, int arrayDelta)
	{
		if (isPieceWhite(heldPiece))
		{
			if (trueFEN.FENBoard[arrayIndex + arrayDelta] != 0
				&& !isWhitePawnCapture(arrayIndex, arrayIndex + arrayDelta))
				return false;
			if (getRank(arrayIndex) == 2 && arrayDelta == -16)
				return true;
			if (arrayDelta == -8)
				return true;

			if (isWhitePawnCapture(arrayIndex, arrayIndex + arrayDelta))
				return true;

			return false;
		}

		if (!isPieceWhite(heldPiece))
		{
			if (trueFEN.FENBoard[arrayIndex + arrayDelta] != 0
				&& !isBlackPawnCapture(arrayIndex, arrayIndex + arrayDelta))
				return false;
			if (getRank(arrayIndex) == 7 && arrayDelta == 16)
				return true;
			if (arrayDelta == 8)
				return true;

			if (isBlackPawnCapture(arrayIndex, arrayIndex + arrayDelta))
				return true;

			return false;
		}
		return false;
	}

	bool pieceLogic::isWhitePawnCapture(int arrayIndex, int targetIndex)
	{
		if (bb::isOutOfRange(targetIndex) || targetIndex < arrayIndex - 9)
			return false;

		for (auto attack : WHITEPAWNATTACK)
			if (trueFEN.FENBoard[arrayIndex + attack] < 0
				|| arrayIndex + attack == trueFEN.enPassantTargetSqr)
				return true;

		return false;
	}

	bool pieceLogic::isBlackPawnCapture(int arrayIndex, int targetIndex)
	{
		if (bb::isOutOfRange(targetIndex) || targetIndex > arrayIndex + 9)
			return false;

		for (auto attack : BLACKPAWNATTACK)
			if (trueFEN.FENBoard[arrayIndex + attack] > 0
				|| arrayIndex + attack == trueFEN.enPassantTargetSqr)
				return true;

		return false;
	}

	bool pieceLogic::kingPsuedoLegal(int arrayIndex, int arrayDelta)
	{
		if (arrayIndex % 8 == 0 && (arrayDelta == -1 || arrayDelta == -9 || arrayDelta == 7))
			return false;
		if ((arrayIndex + 1) % 8 == 0 && (arrayDelta == 1 || arrayDelta == 9 || arrayDelta == -7))
			return false;

		if (castlePsuedoLegal(arrayIndex, arrayIndex + arrayDelta))
			return true;

		if (arrayDelta < 0)
			arrayDelta *= -1;

		if (arrayDelta == 8 || arrayDelta == 7 || arrayDelta == 9 || arrayDelta == 1)
			return true;
		else
			return false;
	}

	bool pieceLogic::castleUnobstructed(int targetIndex)
	{
		if (trueFEN.FENBoard[60] == K && getRank(targetIndex) == 1)
		{
			if (trueFEN.FENBoard[63] == R && trueFEN.FENBoard[61] == 0 && trueFEN.FENBoard[62] == 0 && targetIndex == 62)
				return true;
			if (trueFEN.FENBoard[56] == R && trueFEN.FENBoard[59] == 0 && trueFEN.FENBoard[58] == 0 && trueFEN.FENBoard[57] == 0 && targetIndex == 58)
				return true;
		}
		if (trueFEN.FENBoard[4] == k && getRank(targetIndex) == 8)
		{
			if (trueFEN.FENBoard[7] == r && trueFEN.FENBoard[5] == 0 && trueFEN.FENBoard[6] == 0 && targetIndex == 6)
				return true;
			if (trueFEN.FENBoard[0] == r && trueFEN.FENBoard[1] == 0 && trueFEN.FENBoard[2] == 0 && trueFEN.FENBoard[3] == 0 && targetIndex == 2)
				return true;
		}
		return false;
	}

	bool pieceLogic::castleAttacked(int targetIndex)
	{
		if (trueFEN.FENBoard[60] == K && getRank(targetIndex) == 1)
		{
			if (bb::trialBlackAttacks[60] || bb::trialBlackAttacks[61] || bb::trialBlackAttacks[62] && targetIndex == 62)
				return true;
			if (bb::trialBlackAttacks[60] || bb::trialBlackAttacks[59] || bb::trialBlackAttacks[58] && targetIndex == 58)
				return true;
		}
		if (trueFEN.FENBoard[4] == k && getRank(targetIndex) == 8)
		{
			if (bb::trialWhiteAttacks[4] || bb::trialWhiteAttacks[5] || bb::trialWhiteAttacks[6] && targetIndex == 6)
				return true;
			if (bb::trialWhiteAttacks[2] || bb::trialWhiteAttacks[3] || bb::trialWhiteAttacks[4] && targetIndex == 2)
				return true;
		}
		return false;
	}

	bool pieceLogic::castlePsuedoLegal(int arrayIndex, int targetIndex)
	{
		if (!castleUnobstructed(targetIndex))
			return false;
		if (castleAttacked(targetIndex))
			return false;

		if (getHeldPiece(arrayIndex) == K)
		{
			if (trueFEN.whiteCanCastleKingside && arrayIndex == 60 && targetIndex == 62)
				return true;
			if (trueFEN.whiteCanCastleQueenside && arrayIndex == 60 && targetIndex == 58)
				return true;
		}
		if (getHeldPiece(arrayIndex) == k)
		{
			if (trueFEN.blackCanCastleKingside && arrayIndex == 4 && targetIndex == 6)
				return true;
			if (trueFEN.blackCanCastleQueenside && arrayIndex == 4 && targetIndex == 2)
				return true;
		}
		return false;
	}

	bool pieceLogic::movePsuedoLegal(int arrayIndex, int targetIndex, const std::array<int, 64>& board)
	{
		int heldPiece = board[arrayIndex];
		int arrayModulus = getModulus(arrayIndex, targetIndex);
		int arrayDelta = targetIndex - arrayIndex;

		if (isSquareFriendly(targetIndex, heldPiece))
			return false;

		if (arrayIndex == targetIndex)
			return false;

		if (isSlidingPiece(heldPiece) && isSlidePsuedoLegal(arrayModulus, heldPiece))
		{
			if (slideUnobstructed(arrayIndex, arrayDelta, arrayModulus, board))
				return true;
		}

		if ((heldPiece == N || heldPiece == n) && knightPsuedoLegal(arrayIndex, arrayDelta))
			return true;

		if ((heldPiece == P || heldPiece == p) && pawnPsuedoLegal(heldPiece, arrayIndex, arrayDelta))
			return true;

		if ((heldPiece == K || heldPiece == k) && kingPsuedoLegal(arrayIndex, arrayDelta))
			return true;

		return false;
	}

	bool pieceLogic::inCheck(std::array<bool, BOARDSIZE>& whiteAttackBoard, std::array<bool, BOARDSIZE>& blackAttackBoard)
	{
		if (trueFEN.whiteToMove && blackAttackBoard[trueFEN.trialWhiteKingIndex])
		{
			return true;
		}

		if (!trueFEN.whiteToMove && whiteAttackBoard[trueFEN.trialBlackKingIndex])
		{
			return true;
		}

		return false;
	}

	bool pieceLogic::trialLegal(int arrayIndex, int targetIndex)
	{
		int heldPiece = trueFEN.FENBoard[arrayIndex];

		trueFEN.trialBoard = trueFEN.FENBoard;
		trueFEN.trialBoard[arrayIndex] = 0;
		trueFEN.trialBoard[targetIndex] = heldPiece;

		if (!movePsuedoLegal(arrayIndex, targetIndex, trueFEN.FENBoard))
			return false;

		trueFEN.updateKingIndex(trueFEN.trialBoard, trueFEN.trialWhiteKingIndex, trueFEN.trialBlackKingIndex);

		bb::generateAttackBoards(trueFEN.trialBoard, bb::trialWhiteAttacks, bb::trialBlackAttacks);
		if (inCheck(bb::trialWhiteAttacks, bb::trialBlackAttacks))
		{
			return false;
		}
		return true;
	}

	std::string pieceLogic::isPromotion()
	{
		for (int i = 0; i < 8; i++)
			if (trueFEN.FENBoard[i] == P)
				return "white";

		for (int i = 56; i < 64; i++)
			if (trueFEN.FENBoard[i] == p)
				return "black";

		return "false";
	}

	bool pieceLogic::isSquareFriendly(int targetIndex, int heldPiece)
	{
		if (heldPiece > 0 && trueFEN.FENBoard[targetIndex] > 0)
			return true;

		else if (heldPiece < 0 && trueFEN.FENBoard[targetIndex] < 0)
			return true;
		return false;
	}

	bool pieceLogic::whiteMated()
	{
		int arrayIndex;

		trueFEN.updateKingIndex(trueFEN.FENBoard, trueFEN.whiteKingIndex, trueFEN.blackKingIndex);
		if (trueFEN.whiteToMove)
		{
			arrayIndex = trueFEN.whiteKingIndex;

			if (!bb::trialBlackAttacks[arrayIndex])
			{
				return false;
			}

			for (auto move : KINGMOVES)
			{
				if (bb::isOutOfRange(arrayIndex + move))
					continue;
				if (!bb::trialBlackAttacks[arrayIndex + move] && trueFEN.FENBoard[arrayIndex + move] < 1)
				{
					return false;
				}
			}
			if (whiteCanMove(trueFEN.FENBoard))
			{
				return false;
			}


			std::cout << "WHITE MATED\n";
			return true;
		}
		return false;
	}

	bool pieceLogic::blackMated()
	{
		int arrayIndex;

		trueFEN.updateKingIndex(trueFEN.FENBoard, trueFEN.whiteKingIndex, trueFEN.blackKingIndex);
		if (!trueFEN.whiteToMove)
		{
			arrayIndex = trueFEN.blackKingIndex;

			if (!bb::trialWhiteAttacks[arrayIndex])
			{
				return false;
			}

			for (auto move : KINGMOVES)
			{
				if (bb::isOutOfRange(arrayIndex + move))
					continue;
				if (!bb::trialWhiteAttacks[arrayIndex + move] && trueFEN.FENBoard[arrayIndex + move] > -1)
				{
					return false;
				}
			}
			if (blackCanMove(trueFEN.FENBoard))
			{
				return false;
			}


			return true;
		}
		return false;
	}

	bool pieceLogic::blackCanMove(const std::array<int, 64>& board)
	{
		for (int index = 0; index < BOARDSIZE; index++)
		{
			switch (board[index])
			{
			case p:
				for (auto move : BLACKPAWNMOVES)
				{
					if (bb::isOutOfRange(index + move))
						continue;
					if (trialLegal(index, index + move))
						return true;
				}
				for (auto attack : BLACKPAWNATTACK)
				{
					if (bb::isOutOfRange(index + attack))
						continue;
					if (trialLegal(index, index + attack))
						return true;
				}
				break;
			case n:
				for (auto move : KNIGHTMOVES)
				{
					if (bb::isOutOfRange(index + move))
						continue;
					if (trialLegal(index, index + move))
						return true;
				}
				break;
			case b:
				for (auto move : BISHOPMOVES)
				{
					if (bb::isOutOfRange(index + move))
						continue;
					if (trialLegal(index, index + move))
						return true;
				}
				break;
			case r:
				for (auto move : ROOKMOVES)
				{
					if (bb::isOutOfRange(index + move))
						continue;
					if (trialLegal(index, index + move))
						return true;
				}
				break;
			case q:
				for (auto move : QUEENMOVES)
				{
					if (bb::isOutOfRange(index + move))
						continue;
					if (trialLegal(index, index + move))
						return true;
				}
				break;
			}
		}
		return false;
	}

	bool pieceLogic::whiteCanMove(const std::array<int, 64>& board)
	{
		for (int index = 0; index < BOARDSIZE; index++)
		{
			switch (board[index])
			{
			case P:
				for (auto move : WHITEPAWNMOVES)
				{
					if (bb::isOutOfRange(index + move))
						continue;
					if (trialLegal(index, index + move))
						return true;
				}
				for (auto attack : WHITEPAWNATTACK)
				{
					if (bb::isOutOfRange(index + attack))
						continue;
					if (trialLegal(index, index + attack))
						return true;
				}
				break;
			case N:
				for (auto move : KNIGHTMOVES)
				{
					if (bb::isOutOfRange(index + move))
						continue;
					if (trialLegal(index, index + move))
						return true;
				}
				break;
			case B:
				for (auto move : BISHOPMOVES)
				{
					if (bb::isOutOfRange(index + move))
						continue;
					if (trialLegal(index, index + move))
						return true;
				}
				break;
			case R:
				for (auto move : ROOKMOVES)
				{
					if (bb::isOutOfRange(index + move))
						continue;
					if (trialLegal(index, index + move))
						return true;
				}
				break;
			case Q:
				for (auto move : QUEENMOVES)
				{
					if (bb::isOutOfRange(index + move))
						continue;
					if (trialLegal(index, index + move))
						return true;
				}
				break;
			}
		}
		return false;
	}

	bool pieceLogic::isDraw()
	{
		int whiteIndex = trueFEN.whiteKingIndex;
		int blackIndex = trueFEN.blackKingIndex;

		// stalemate
		if (!trueFEN.whiteToMove && !blackCanMove(trueFEN.FENBoard) && !bb::trialWhiteAttacks[trueFEN.blackKingIndex])
		{
			for (auto move : KINGMOVES)
			{
				if (bb::isOutOfRange(blackIndex + move))
					continue;
				if (!movePsuedoLegal(blackIndex, blackIndex + move, trueFEN.FENBoard))
					continue;
				if (!bb::trialWhiteAttacks[blackIndex + move] && trueFEN.FENBoard[blackIndex + move] > -1)
				{
					printf("%d\n", blackIndex + move);
					return false;
				}
			}
			return true;
		}

		if (trueFEN.whiteToMove && !whiteCanMove(trueFEN.FENBoard) && !bb::trialBlackAttacks[trueFEN.whiteKingIndex])
		{
			for (auto move : KINGMOVES)
			{
				if (bb::isOutOfRange(whiteIndex + move))
					continue;
				if (!movePsuedoLegal(whiteIndex, whiteIndex + move, trueFEN.FENBoard))
					continue;
				if (!bb::trialBlackAttacks[whiteIndex + move] && trueFEN.FENBoard[whiteIndex + move] < 1)
				{
					return false;
				}
			}
			return true;
		}

		return false;
	}

	bool pieceLogic::moveLegal(int arrayIndex, int targetIndex)
	{
		int heldPiece = trueFEN.FENBoard[arrayIndex];

		// colour check
		if (trueFEN.whiteToMove && !isPieceWhite(heldPiece))
			return false;
		if (!trueFEN.whiteToMove && isPieceWhite(heldPiece))
			return false;

		if (movePsuedoLegal(arrayIndex, targetIndex, trueFEN.FENBoard))
		{
			if (!PieceLogic.trialLegal(arrayIndex, targetIndex))
				return false;

			// en passant capture
			if (heldPiece == P && PieceLogic.isWhitePawnCapture(arrayIndex, targetIndex)
				&& trueFEN.FENBoard[targetIndex] == 0)
				trueFEN.FENBoard[targetIndex + 8] = 0;
			else if (heldPiece == p && PieceLogic.isBlackPawnCapture(arrayIndex, targetIndex)
				&& trueFEN.FENBoard[targetIndex] == 0)
				trueFEN.FENBoard[targetIndex - 8] = 0;

			// en passant square
			if (heldPiece == P && arrayIndex - targetIndex == 16)
				trueFEN.enPassantTargetSqr = targetIndex + 8;
			else if (heldPiece == p && targetIndex - arrayIndex == 16)
				trueFEN.enPassantTargetSqr = targetIndex - 8;
			else
				trueFEN.enPassantTargetSqr = NULL;

			// tracking castling rights
			if (trueFEN.FENBoard[0] != r)
				trueFEN.blackCanCastleQueenside = false;
			if (trueFEN.FENBoard[7] != r)
				trueFEN.blackCanCastleKingside = false;
			if (trueFEN.FENBoard[56] != R)
				trueFEN.whiteCanCastleQueenside = false;
			if (trueFEN.FENBoard[63] != R)
				trueFEN.whiteCanCastleKingside = false;
			if (trueFEN.FENBoard[4] != k)
			{
				trueFEN.blackCanCastleKingside = false;
				trueFEN.blackCanCastleQueenside = false;
			}
			if (trueFEN.FENBoard[60] != K)
			{
				trueFEN.whiteCanCastleKingside = false;
				trueFEN.whiteCanCastleQueenside = false;
			}

			// white castling rook interactions
			if (heldPiece == K && targetIndex == 62)
			{
				trueFEN.FENBoard[61] = R;
				trueFEN.FENBoard[63] = 0;
			}
			else if (heldPiece == K && targetIndex == 58)
			{
				trueFEN.FENBoard[59] = R;
				trueFEN.FENBoard[56] = 0;
			}

			// black castling rook interactions
			if (heldPiece == k && targetIndex == 6)
			{
				trueFEN.FENBoard[5] = r;
				trueFEN.FENBoard[7] = 0;
			}
			else if (heldPiece == k && targetIndex == 2)
			{
				trueFEN.FENBoard[3] = r;
				trueFEN.FENBoard[0] = 0;
			}

			trueFEN.whiteToMove = !trueFEN.whiteToMove;
			return true;
		}
		return false;
	}

	// struct init
	pieceLogic PieceLogic;

	// Distance struct
	std::array<Distance, BOARDSIZE> genDistances()
	{
		std::array<Distance, BOARDSIZE> distances;

		bool orthTo8Checked, orthTo1Checked, orthToHChecked, orthToAChecked,
			diagToA8Checked, diagToA1Checked, diagToH8Checked, diagToH1Checked;
		for (int i = 0; i < BOARDSIZE; i++)
		{
			orthTo8Checked = orthTo1Checked = orthToHChecked = orthToAChecked =
				diagToA8Checked = diagToA1Checked = diagToH8Checked = diagToH1Checked = false;

			while (!(orthTo8Checked && orthTo1Checked && orthToHChecked && orthToAChecked
				&& diagToA8Checked && diagToA1Checked && diagToH8Checked && diagToH1Checked))
			{
				// orthTo8
				if (i - 8 - (8 * distances[i].orthTo8) < 0)
					orthTo8Checked = true;
				else
					distances[i].orthTo8++;

				// orthTo1
				if (i + 8 + (8 * distances[i].orthTo1) > 63)
					orthTo1Checked = true;
				else
					distances[i].orthTo1++;

				// orthToH
				if ((i + 1 + distances[i].orthToH) % 8 == 0)
					orthToHChecked = true;
				else
					distances[i].orthToH++;

				// orthToA
				if ((i - distances[i].orthToA) % 8 == 0)
					orthToAChecked = true;
				else
					distances[i].orthToA++;

				// diagToA8
				if ((i - 9 * distances[i].diagToA8) % 8 == 0 ||
					i - (9 * distances[i].diagToA8) < 8)
					diagToA8Checked = true;
				else
					distances[i].diagToA8++;

				// diagToA1
				if ((i + 7 * distances[i].diagToA1) % 8 == 0 ||
					i + (7 * distances[i].diagToA1) > 55)
					diagToA1Checked = true;
				else
					distances[i].diagToA1++;

				// diagToH8
				if ((i + 1 - 7 * distances[i].diagToH8) % 8 == 0 ||
					i - (7 * distances[i].diagToH8) < 8)
					diagToH8Checked = true;
				else
					distances[i].diagToH8++;

				// diagToH1
				if ((i + 1 + 9 * distances[i].diagToH1) % 8 == 0 ||
					i + (9 * distances[i].diagToH1) > 55)
					diagToH1Checked = true;
				else
					distances[i].diagToH1++;
			}
		}
		return distances;
	}

	// array containing all board square distances
	std::array<Distance, BOARDSIZE> distanceArrays = genDistances();

	int slideToEdge(int arrayIndex, int delta)
	{
		switch (delta)
		{
		case -9:
			return distanceArrays[arrayIndex].diagToA8;
		case -8:
			return distanceArrays[arrayIndex].orthTo8;
		case -7:
			return distanceArrays[arrayIndex].diagToH8;
		case -1:
			return distanceArrays[arrayIndex].orthToA;
		case 1:
			return distanceArrays[arrayIndex].orthToH;
		case 7:
			return distanceArrays[arrayIndex].diagToA1;
		case 8:
			return distanceArrays[arrayIndex].orthTo1;
		case 9:
			return distanceArrays[arrayIndex].diagToH1;
		default:
			return 0;
		}
	}
}