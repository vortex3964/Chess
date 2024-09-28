#include "King.h"

King::King() :Piece() {
	
}

King::King(int colour) :Piece(colour, pt::KING) {

}

void King::possible_moves(int y_pos, int x_pos, Piece* board[8][8]) {
	std::vector<std::pair<int, int>> moves = {
			{1,-1},{ 1,0 },{ 1,1 },{ 0, -1},
			{0, 1},{-1,-1},{-1,0},{-1,1}
	};

	for (auto move : moves) {
		int newy = y_pos + move.first;
		int newx = x_pos + move.second;
		if (newx >= 0 && newx < 8 && newy >= 0 && newy < 8) {
			if (board[newy][newx] != nullptr && board[newy][newx]->get_colour() == get_colour()) continue;
			if (board[newy][newx] != nullptr && board[newy][newx]->get_colour() != get_colour()) {
				board[newy][newx]->make_Capturable();
			}
			board[newy][newx]->add_to_moves(newy, newx);
		}
	}
}


Piece* King::clone() {
	return new King(*this);
}
