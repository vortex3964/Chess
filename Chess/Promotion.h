#pragma once
#include "chess_pieces/Piece_types.h"
#include "chess_pieces/Rook.h"
#include "chess_pieces/Bishop.h"
#include "chess_pieces/Knight.h"
#include "chess_pieces/Pawn.h"
#include "chess_pieces/Queen.h"
#include "SFML/Graphics.hpp"

class Promotion
{
public:
	static void promote(Piece* &board);
};

