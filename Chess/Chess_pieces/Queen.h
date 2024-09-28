#pragma once
#include "piece.h"

class Queen :public Piece
{
public:
	Queen();
	Queen(int colour);
	void possible_moves(int y_pos, int x_pos, Piece* Board[8][8]);
	Piece* clone();
};

