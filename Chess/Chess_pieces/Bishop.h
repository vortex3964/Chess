#pragma once
#include "Piece.h"

class Bishop :public Piece
{
public:
	Bishop();
	Bishop(int colour);
	void possible_moves(int y_pos, int x_pos, Piece* board[8][8]);
	Piece* clone();
};

