#pragma once
#include "piece.h"
class King :public Piece
{
public:
	King();
	King(int colour);
	void possible_moves(int y_pos, int x_pos, Piece* board[8][8]);
	Piece* clone();
};
