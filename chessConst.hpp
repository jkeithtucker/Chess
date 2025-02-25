#pragma once
#include "pch.hpp"

// chess logic related defines
const int BOARDSIZE = 64;
const int P = 1;
const int N = 2;
const int B = 3;
const int R = 4;
const int Q = 5;
const int K = 6;
const int p = -1;
const int n = -2;
const int b = -3;
const int r = -4;
const int q = -5;
const int k = -6;

// piece movement defines
const std::array<int, 2> WHITEPAWNMOVES{ -8, 16 };
const std::array<int, 2> WHITEPAWNATTACK{ -9, -7 };
const std::array<int, 2> BLACKPAWNMOVES{ 8, 16 };
const std::array<int, 2> BLACKPAWNATTACK{ 7, 9 };
const std::array<int, 8> KNIGHTMOVES{ -17, -15, -10, -6, 6, 10, 15, 17 };
const std::array<int, 4> BISHOPMOVES{ -9, -7, 7, 9 };
const std::array<int, 4> ROOKMOVES{ -8, -1, 1, 8 };
const std::array<int, 8> QUEENMOVES{ -9, -8, -7, -1, 1, 7, 8, 9 };
const std::array<int, 8> KINGMOVES{ -9, -8, -7, -1, 1, 7, 8, 9 };

