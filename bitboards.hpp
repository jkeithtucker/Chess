#pragma once

#include "pch.hpp"
#include "fen.hpp"

namespace bb
{
	// bitboards
	extern std::array<bool, BOARDSIZE> whiteAttacks, trialWhiteAttacks;
	extern std::array<bool, BOARDSIZE> blackAttacks, trialBlackAttacks;
	extern std::array<bool, BOARDSIZE> occupiedSquares;

	// funcs
	void generateAttackBoards(const std::array<int, BOARDSIZE>& board, std::array<bool, BOARDSIZE>& whiteAttackBoard, std::array<bool, BOARDSIZE>& blackAttackBoard);

	void generateWhiteAttackBoard(const int arrayIndex, const std::array<int, BOARDSIZE>& board, std::array<bool, BOARDSIZE>& whiteAttackBoard);
	void generateBlackAttackBoard(const int arrayIndex, const std::array<int, BOARDSIZE>& board, std::array<bool, BOARDSIZE>& blackAttackBoard);

	void whitePawnAttacks(const int arrayIndex, std::array<bool, BOARDSIZE>& attackBoard);

	void blackPawnAttacks(const int arrayIndex, std::array<bool, BOARDSIZE>& attackBoard);

	void knightAttacks(const int arrayIndex, std::array<bool, BOARDSIZE>& attackBoard, const std::array<int, 64>& board);

	void bishopAttacks(const int arrayIndex, std::array<bool, BOARDSIZE>& attackBoard, const std::array<int, 64>& board);

	void rookAttacks(const int arrayIndex, std::array<bool, BOARDSIZE>& attackBoard, const std::array<int, 64>& board);

	void queenAttacks(const int arrayIndex, std::array<bool, BOARDSIZE>& AttackBoard, const std::array<int, 64>& board);

	void kingAttacks(const int arrayIndex, std::array<bool, BOARDSIZE>& attackBoard, const std::array<int, 64>& board);

	void clearAttackBoards(std::array<bool, BOARDSIZE>& whiteAttackBoard, std::array<bool, BOARDSIZE>& blackAttackBoard);

	bool isOutOfRange(int x);

	void generateOccupiedSquares();
}