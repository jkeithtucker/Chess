#pragma once

#include "pch.hpp"

// example FENs
extern const std::string defStart, najdorfPoisonPawn, pawnBreakthrough, berlinEndgame, debugPosition;

// FEN class
class FEN
{
public:
	std::string m_ranks, m_toMove, m_castling, m_enPassantSqr, m_drawCounter, m_moveNum;

public:
	std::array<int, 64> FENBoard, trialBoard;
	int enPassantTargetSqr, moveLimitDraw, moveNum;
	bool whiteToMove, whiteCanCastleKingside, whiteCanCastleQueenside, blackCanCastleKingside, blackCanCastleQueenside;
	int whiteKingIndex, trialWhiteKingIndex, blackKingIndex, trialBlackKingIndex;

private:
	void fillEmptyRankSqrs(std::array<int, 64>& workBoard, int boardStart, int boardEnd);

	std::array<int, 64> stringRanksToBoard(std::string FEN);

	bool isWhiteToMove(std::string sideToMoveFEN);

	void CastleStringToVariables(std::string castleFEN);

	int enPassantStringToIndex(std::string enPasFEN);

	int drawCounterStringToInt(std::string drawCountFEN);

	int moveNumStringToInt(std::string moveNumFEN);

public:
	FEN(const std::string& FEN);

	~FEN();

	void convertStringToVariables();

	void updateKingIndex(const std::array<int, BOARDSIZE> board, int& whiteIndex, int& blackIndex);
};

// true FEN is the FEN of the currrent board state
extern FEN trueFEN;
