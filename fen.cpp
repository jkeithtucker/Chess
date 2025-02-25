#include "pch.hpp"
#include "fen.hpp"

// example FENs
const std::string defStart = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
const std::string najdorfPoisonPawn = "rnb1kb1r/1p3ppp/p2ppn2/6B1/3NPP2/2N5/PqPQ2PP/R3KB1R w KQkq - 0 9";
const std::string pawnBreakthrough = "8/5ppp/8/5PPP/8/k7/8/K7 w - - 0 1";
const std::string berlinEndgame = "r1bk1b1r/ppp2ppp/2p5/4Pn2/8/5N2/PPP2PPP/RNB2RK1 w - - 0 9";
const std::string debugPosition = "8/1k1q1r1p/8/1b1nb3/1B1NB3/8/1K1Q1R1P/8 w - - 0 1";

// FEN class def
FEN::FEN(const std::string& FEN)
{
	int spaceCount = 0;

	for (int i = 0; i < FEN.size(); i++)
	{
		if (FEN.at(i) == ' ')
		{
			spaceCount++;
			i++;
		}


		switch (spaceCount)
		{
		case 0:
			m_ranks.push_back(FEN.at(i));
			break;

		case 1:
			m_toMove.push_back(FEN.at(i));
			break;

		case 2:
			m_castling.push_back(FEN.at(i));
			break;

		case 3:
			m_enPassantSqr.push_back(FEN.at(i));
			break;

		case 4:
			m_drawCounter.push_back(FEN.at(i));
			break;

		case 5:
			m_moveNum.push_back(FEN.at(i));
			break;
		}
	}
	convertStringToVariables();
}

FEN::~FEN()
{
	; // nothing for now
}

// sub-funcs
void FEN::fillEmptyRankSqrs(std::array<int, BOARDSIZE>& workBoard, int boardStart, int boardEnd)
{
	for (int i = boardStart; i < boardEnd; i++)
		workBoard[i] = 0;
}

std::array<int, BOARDSIZE> FEN::stringRanksToBoard(std::string FEN)
{
	int i, j;
	std::array<int, BOARDSIZE> workBoard;

	i = j = 0;
	while (i < BOARDSIZE)
	{
		switch (FEN[j])
		{
		case 'p':
			workBoard[i] = p;
			i++;
			j++;
			break;

		case 'n':
			workBoard[i] = n;
			i++;
			j++;
			break;

		case 'b':
			workBoard[i] = b;
			i++;
			j++;
			break;

		case 'r':
			workBoard[i] = r;
			i++;
			j++;
			break;

		case 'q':
			workBoard[i] = q;
			i++;
			j++;
			break;

		case 'k':
			workBoard[i] = k;
			this->blackKingIndex = this->trialBlackKingIndex = i;
			i++;
			j++;
			break;

		case 'P':
			workBoard[i] = P;
			i++;
			j++;
			break;

		case 'N':
			workBoard[i] = N;
			i++;
			j++;
			break;

		case 'B':
			workBoard[i] = B;
			i++;
			j++;
			break;

		case 'R':
			workBoard[i] = R;
			i++;
			j++;
			break;

		case 'Q':
			workBoard[i] = Q;
			i++;
			j++;
			break;

		case 'K':
			workBoard[i] = K;
			this->whiteKingIndex = this->trialWhiteKingIndex = i;
			i++;
			j++;
			break;

		case '1':
			workBoard[i] = 0;
			i++;
			j++;
			break;

		case '2':
			fillEmptyRankSqrs(workBoard, i, i + 2);
			i += 2;
			j++;
			break;

		case '3':
			fillEmptyRankSqrs(workBoard, i, i + 3);
			i += 3;
			j++;
			break;

		case '4':
			fillEmptyRankSqrs(workBoard, i, i + 4);
			i += 4;
			j++;
			break;

		case '5':
			fillEmptyRankSqrs(workBoard, i, i + 5);
			i += 5;
			j++;
			break;

		case '6':
			fillEmptyRankSqrs(workBoard, i, i + 6);
			i += 6;
			j++;
			break;

		case '7':
			fillEmptyRankSqrs(workBoard, i, i + 7);
			i += 7;
			j++;
			break;

		case '8':
			fillEmptyRankSqrs(workBoard, i, i + 8);
			i += 8;
			j++;
			break;

		case '/':
			j++;
			break;
		}
	}
	return workBoard;
}

bool FEN::isWhiteToMove(std::string sideToMoveFEN)
{
	if (sideToMoveFEN == "w")
		return true;
	else
		return false;
}

void FEN::CastleStringToVariables(std::string castleFEN)
{
	whiteCanCastleKingside = whiteCanCastleQueenside = blackCanCastleKingside = blackCanCastleQueenside = false;

	for (auto a : castleFEN)
	{
		switch (a)
		{
		case 'K':
			whiteCanCastleKingside = true;
			break;
		case 'Q':
			whiteCanCastleQueenside = true;
			break;
		case 'k':
			blackCanCastleKingside = true;
			break;
		case 'q':
			blackCanCastleQueenside = true;
			break;
		case '-':
			return;
		}
	}
}

int FEN::enPassantStringToIndex(std::string enPasFEN)
{
	if (enPasFEN.size() == 1)
		return -1;

	int rank = (7 - (enPasFEN[1] - 49)) * 8;
	int file = enPasFEN[0] - 97;

	enPassantTargetSqr = rank + file;
	return enPassantTargetSqr;
}

int FEN::drawCounterStringToInt(std::string drawCountFEN)
{
	return std::stoi(drawCountFEN);
}

int FEN::moveNumStringToInt(std::string moveNumFEN)
{
	return stoi(moveNumFEN);
}

// supra-func
void FEN::convertStringToVariables()
{
	this->FENBoard = stringRanksToBoard(m_ranks);

	this->whiteToMove = isWhiteToMove(m_toMove);

	CastleStringToVariables(m_castling);

	this->enPassantTargetSqr = enPassantStringToIndex(m_enPassantSqr);

	this->moveLimitDraw = drawCounterStringToInt(m_drawCounter);

	this->moveNum = moveNumStringToInt(m_moveNum);

	/* example FEN string after 1.e4 c5:
	rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2

	rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR = m_ranks
	w = m_toMove
	KQkq = m_castling
	c6 = m_enPassantSqr
	0 = m_drawCounter
	2 = m_moveNum
	*/
}

void FEN::updateKingIndex(const std::array<int, BOARDSIZE> board, int& whiteIndex, int& blackIndex)
{
	for (int i = 0; i < BOARDSIZE; i++)
	{
		if (board[i] == K)
		{
			whiteIndex = i;
		}

		if (board[i] == k)
		{
			blackIndex = i;
		}
	}
}

// class init
FEN trueFEN(defStart);