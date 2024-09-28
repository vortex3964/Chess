#pragma once
#include "Piece.h"
class Knight :public Piece
{
public:
	Knight();
	Knight(int colour);
	void possible_moves(int y_pos, int x_pos, Piece* board[8][8]);
	Piece* clone();
};
