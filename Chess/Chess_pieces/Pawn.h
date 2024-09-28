#pragma once
#include "Piece.h"




class Pawn :public Piece
{
public:
	static int y;
	static int x;
	static int colour;
	static bool exists;
	Pawn();
	Pawn(int colour);
	void possible_moves(int y_pos, int x_pos, Piece* board[8][8]);
	Piece* clone();
};



