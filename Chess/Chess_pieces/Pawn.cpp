#include "Pawn.h"

 int  Pawn::y=0;
 int  Pawn::x=0;
 int  Pawn::colour=0;
 bool Pawn::exists=false;

Pawn::Pawn() :Piece() {

}

Pawn::Pawn(int colour) :Piece(colour, pt::PAWN) {

}

void Pawn::possible_moves(int y_pos, int x_pos, Piece* board[8][8]) {
	int incr = (get_colour()) ? incr = +1 : incr = -1;//the increment depending on the pawns colour
	
	//if the pawn has not moved and nothing is blocking it it can advance 2 squares
	if (!hasItMoved() && board[y_pos + incr][x_pos] == nullptr && board[y_pos + incr + incr][x_pos] == nullptr) {
		Piece::add_to_moves(y_pos + incr + incr, x_pos);
	}
	if (board[y_pos + incr][x_pos] == nullptr) 
	{
		Piece::add_to_moves(y_pos + incr, x_pos);//the pawn can advance a square if its not blocked by a pice
	}

	//pawns can capture diagonally
	if(x_pos + 1<8 && board[y_pos + incr][x_pos + 1] != nullptr && board[y_pos + incr][x_pos + 1]->get_colour() != get_colour()) {
		board[y_pos + incr][x_pos + 1]->make_Capturable();
		add_to_moves(y_pos + incr, x_pos + 1);
	}

	if (x_pos-1>=0 && board[y_pos + incr][x_pos - 1] != nullptr && board[y_pos + incr][x_pos - 1]->get_colour() != get_colour()) {
		board[y_pos + incr][x_pos - 1]->make_Capturable();
		add_to_moves(y_pos + incr, x_pos - 1);
	}

	if (x_pos+1<7 && exists && board[y+incr][x]==nullptr && y_pos==y && x==x_pos+1) {
		add_to_moves(y + incr,x);
	}
	else if (x-1>=0 && exists && board[y + incr][x] == nullptr && y_pos == y && x == x_pos-1) {
		add_to_moves(y + incr, x);
	}
}

Piece* Pawn::clone() {
	return new Pawn(*this);
}

