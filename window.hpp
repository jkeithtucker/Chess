#pragma once

#include "pch.hpp"

// window
const sf::Vector2i winRes(1280, 720);
const sf::Vector2f spriteScale(0.5f, 0.5f);
const int boardOffset = 80;
const int sqrSize = 50;
const int boardEnd = boardOffset + sqrSize * 8;

// board
const sf::Color Brown(155, 103, 60);
const sf::Color Prom(200, 0, 0, 200);
extern sf::RectangleShape brdSqr;

// sprite struct
struct SpriteStruct
{
	sf::Sprite* whitePawn;
	sf::Sprite* whiteKnight;
	sf::Sprite* whiteBishop;
	sf::Sprite* whiteRook;
	sf::Sprite* whiteQueen;
	sf::Sprite* whiteKing;

	sf::Sprite* blackPawn;
	sf::Sprite* blackKnight;
	sf::Sprite* blackBishop;
	sf::Sprite* blackRook;
	sf::Sprite* blackQueen;
	sf::Sprite* blackKing;
};

// funcs
SpriteStruct* loadSprites(void);

void drawBoard(sf::RenderWindow* window);

sf::RenderWindow* createWin(void);

void drawPieces(sf::RenderWindow* window, const SpriteStruct* sprites, std::array<int, BOARDSIZE> board);

void dragPiece(sf::RenderWindow* window, const SpriteStruct* sprites, int heldPiece, std::array<int, BOARDSIZE> renderBoard);

void movePiece(sf::RenderWindow* window, const SpriteStruct* sprites);

void drawPromotion(sf::RenderWindow* window, const SpriteStruct* sprites, int index);

void promotionChoice(sf::RenderWindow* window, const int targetIndex);
