#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"

Queen::Queen() :Piece() {

}

Queen::Queen(int colour) :Piece(colour, pt::QUEEN) {

}

void Queen::possible_moves(int y_pos, int x_pos, Piece* Board[8][8]) {
	Rook r=Rook(Queen::get_colour());
	Bishop b=Bishop(Queen::get_colour());
	r.possible_moves(y_pos,x_pos,Board);
	b.possible_moves(y_pos, x_pos, Board);
}

Piece* Queen::clone() {
	return new Queen(*this);
}