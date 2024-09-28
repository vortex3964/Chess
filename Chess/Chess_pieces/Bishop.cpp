#include "Bishop.h"

Bishop::Bishop(int colour) :Piece(colour, pt::BISHOP)
{

}

Bishop::Bishop() :Piece() {

}

void Bishop::possible_moves(int y_pos, int x_pos, Piece* board[8][8]) {
	int x = x_pos + 1;
	int y = y_pos + 1;

	while (y < 8 && x < 8 && board[y][x] == nullptr) {
		board[y][x]->add_to_moves(y, x); // Correct assignment
		x++;  // Move diagonally down-right
		y++;
	}

	if (y < 8 && x < 8 && board[y][x] != nullptr) {
		if (board[y][x]->get_colour() !=get_colour()) {
			board[y][x]->make_Capturable();
			board[y][x]->add_to_moves(y, x);
		}
	}

	// up-right
	x = x_pos + 1;
	y = y_pos - 1;

	while (y >= 0 && x < 8 && board[y][x] == nullptr) {
		board[y][x]->add_to_moves(y,x);
		x++;  // Move diagonally up-right
		y--;
	}

	if (y >= 0 && x < 8 && board[y][x] != nullptr) {
		if (board[y][x]->get_colour() != get_colour()) {
			board[y][x]->make_Capturable();
			board[y][x]->add_to_moves(y, x);
		}
	}



	// up-left
	x = x_pos - 1;
	y = y_pos - 1;

	while (y >= 0 && x >= 0 &&board[y][x] == nullptr) {
		board[y][x]->add_to_moves(y, x);
		x--;  // Move diagonally up-left
		y--;
	}

	if (y >= 0 && x >= 0 && board[y][x] != nullptr) {
		if (board[y][x]->get_colour() != get_colour()) {
			board[y][x]->add_to_moves(y, x);
			board[y][x]->make_Capturable();
		}
	}

	// down-left
	x = x_pos - 1;
	y = y_pos + 1;

	while (y < 8 && x >= 0 && board[y][x] == nullptr) {
		board[y][x]->add_to_moves(y, x);
		x--;  // Move diagonally down-left
		y++;
	}

	if (y < 8 && x >= 0 && board[y][x] != nullptr) {
		if (board[y][x]->get_colour() != get_colour()) {
			board[y][x]->add_to_moves(y, x);
			board[y][x]->make_Capturable();
		}
	}
}

Piece* Bishop::clone() {
	return new Bishop(*this);
}